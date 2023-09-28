#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <main.hpp>

class Client {
	private:
		std::string		_nickname;
		std::string		_username;
		bool			_isAuthenticated;

	public:
		Client();
		~Client();
		Client(const Client &copy);
		Client &operator=(const Client &copy);

		void	setNickname(std::string nickname);
		void	setUsername(std::string username);
		void	login(bool is_logged_in);

		std::string	getNickname();
		std::string	getUsername();
		bool		isAuthenticated();

		static void	sendMessage(int socket, std::string message);
};

#endif