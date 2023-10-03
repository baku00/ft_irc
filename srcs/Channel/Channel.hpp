#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "../Utils/Message/Message.hpp"

class Mode;

class Channel {
	private:
		std::string	_name;
		std::string _topic;
		Mode 		*_mode;
		std::vector<int>		_users;
		std::vector<int>		_operators;
		std::vector<Message>	_messages;

	public:
		Channel(std::string name, bool by_name);
		Channel();
		~Channel();
		Channel(const Channel &copy);

		Channel		&operator=(const Channel &copy);

		std::string	getName();

		Mode		&mode();
};

std::iostream &operator<<(std::iostream &stream, Channel &client);

#endif