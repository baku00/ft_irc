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
		std::string					_firstname;
		std::string					_lastname;
		std::string					_command;
		std::vector<std::string>	_args;
		bool						_isAuthenticated;
		bool						_isValidate;
		int							_fd;

		void						validate();
		bool						isValidNickname(std::string nickname);

	public:
		Client(int fd, bool by_fd);
		Client();
		~Client();
		Client(const Client &copy);

		Client						&operator=(const Client &copy);

		void						login(bool is_logged_in);

		std::string					getNickname();
		std::string					getUsername();
		std::string					getFirstname();
		std::string					getLastname();
		std::string					getCommand();
		std::vector<std::string>	getArgs();
		int							getFd();
		std::string					getInfo();

		void						setCommand(std::string command);
		void						setArgs(std::vector<std::string> args);
		void						setNickname(std::string nickname);
		void						setUsername(std::string username);
		void						setUserInfo(std::string username, std::string firstname, std::string lastname);
		void						setFirstname(std::string firstname);
		void						setLastname(std::string lastname);
		bool						isAuthenticated();
		bool						isValidate();

		static void					sendMessage(int socket, std::string message);
};

std::iostream &operator<<(std::iostream &stream, Client &client);

#endif