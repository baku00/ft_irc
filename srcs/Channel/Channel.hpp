#ifndef CHANNEL_HPP
# define CHANNEL_HPP

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
# include "../Client/Client.hpp"
# include "../Utils/Message/Message.hpp"

class Channel {
	private:
		std::string					_name;
		std::vector<int>			_clients;
		std::vector<Message *>		_messages;

	public:
		Channel();
		~Channel();
		Channel(const Channel &copy);

		Channel						&operator=(const Channel &copy);

		std::string					getName();
		void						setName(std::string name);

		void						addClient(int fd);
		std::vector<int>			getClients();
		bool						hasClient(int fd);
		void						showClients();

		void						sendMessage(Client *sender, std::string message);
};

std::iostream &operator<<(std::iostream &stream, Channel &client);

#endif