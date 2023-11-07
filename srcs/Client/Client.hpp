#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <main.hpp>
# include <cstdarg>
# include <string>
# include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


class Client {
	private:
		std::string					_nickname;
		std::string					_username;
		std::string					_hostname;
		std::string					_serverName;
		std::string					_realName;
		std::string					_input;

		bool						_isAuthenticated;
		bool						_isValidate;
		int							_fd;

		void						validate();

	public:
		Client();
        Client(int fd);
        ~Client();
        Client(const Client &copy);

		Client						&operator=(const Client &copy);

		void						login(bool is_logged_in);

		std::string					getNickname();
		std::string					getUsername();
		std::string					getHostname();
		std::string					getServername();
		std::string					getRealname();
		std::string					getFullname();
		int							getFd();
		std::string					getInfo();
		std::string					getInput();

		void						setNickname(std::string nickname);
		void						setUsername(std::string username);
		void						setUserInfo(std::string username, std::string hostname, std::string servername, std::string realname);
		void						setHostname(std::string hostname);
		void						setServername(std::string servername);
		void						setRealname(std::string realname);
		void						setCommand(std::string command);
		void						addInput(std::string input);
		void						clearInput();

		bool						isAuthenticated();
		bool						isValidate();

		void						sendMessage(Client *sender, std::string message);
		void						sendChanMsg(Client *sender, std::string channel, std::string message);
		void						sendPrivMsg(Client *sender, std::string message);
		void						reply(std::string code, std::string message...);

		// This method is not meant to be called directly, prefer one of the non-static methods
		static void					sendMessage(int socket, std::string message);

};

std::iostream &operator<<(std::iostream &stream, Client &client);

#endif
