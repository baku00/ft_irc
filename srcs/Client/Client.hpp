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
		std::string					_command;
		std::vector<std::string>	_args;
		bool						_isAuthenticated;
		int							_fd;

	public:
		Client(int fd);
		Client();
		~Client();
		Client(const Client &copy);
		Client &operator=(const Client &copy);

		void	setNickname(std::string nickname);
		void	setUsername(std::string username);
		void	login(bool is_logged_in);

		std::string					getNickname();
		std::string					getUsername();
		std::string					getCommand();
		std::vector<std::string>	getArgs();
		int							getFd();

		void						setCommand(std::string command);
		void						setArgs(std::vector<std::string> args);
		bool						isAuthenticated();

		static void	sendMessage(int socket, std::string message);
};

#endif