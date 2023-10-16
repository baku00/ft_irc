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

#include <bitset>
typedef std::bitset<5> t_mode;

class Channel {
	private:
		std::string					_name;
		std::vector<int>			_clients;
		std::vector<Message *>		_messages;
		t_mode						_mode;

	public:
		Channel();
		~Channel();
		Channel(const Channel &copy);

		enum Mode
		{
			BASE_MASK	= 0b11111,
			I_INVITE	= 0b10000,
			T_TOPIC		= 0b01000,
			K_PASSWORD	= 0b00100,
			O_OPERATOR	= 0b00010,
			L_LIMIT		= 0b00001
		};

		// static const

		Channel						&operator=(const Channel &copy);

		std::string					getName();
		void						setName(std::string name);

		void						addClient(int fd);
		std::vector<int>			getClients();
		bool						hasClient(int fd);
		void						showClients();

		void						sendMessage(Client *sender, std::string message);


		bool						hasMode(t_mode mode);
		void						addMode(t_mode mode);
		void						delMode(t_mode mode);
};

std::iostream &operator<<(std::iostream &stream, Channel &client);

#endif