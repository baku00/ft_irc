#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <vector>
# include <cstring>
# include <cstdio>
# include <cstdlib>
# include <unistd.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <poll.h>
# include <stdio.h>
# include <map>
# include <exception>

class Client {
	private:
		std::string					_nickname;
		std::string					_username;
		std::string					_hostname;
		std::string					_serverName;
		std::string					_realName;
		bool						_isAuthenticated;
		bool						_isValidate;
		int							_fd;

		void						validate();

	public:
		Client(int fd, bool by_fd);
		Client();
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

		void						setNickname(std::string nickname);
		void						setUsername(std::string username);
		void						setUserInfo(std::string username, std::string hostname, std::string servername, std::string realname);
		void						setHostname(std::string hostname);
		void						setServername(std::string servername);
		void						setRealname(std::string realname);
		bool						isAuthenticated();
		bool						isValidate();
		void						sendMessage(Client *sender, std::string message);

		static void					sendMessage(int socket, std::string message);
};

std::iostream &operator<<(std::iostream &stream, Client &client);

#endif