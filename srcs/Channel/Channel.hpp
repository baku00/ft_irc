#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <vector>
# include <string>
# include <map>

# include "../Utils/Message/Message.hpp"
# include "../Server/Instance/ServerInstance.hpp"
# include "../Client/Client.hpp"

class Channel {
	private:
		std::string				_name;
		std::string 			_topic;
		std::vector<int>		_clients;
		std::vector<int>		_operators;
		std::vector<Message>	_messages;

		bool					isValidName(std::string name);

	public:
		Channel(std::string name, bool by_name);
		Channel();
		~Channel();
		Channel(const Channel &copy);

		Channel		&operator=(const Channel &copy);

		std::string	getName();

		void				addClient(int fd);
		bool				hasClient(int fd);
		std::vector<int>	&getClients();

		void		sendMessage(Message message);

};

std::iostream &operator<<(std::iostream &stream, Channel &client);

#endif