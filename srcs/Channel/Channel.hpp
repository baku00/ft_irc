#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <main.hpp>
# include "../Client/Client.hpp"
# include "../Utils/Message/Message.hpp"
# include <bitset>
#include "../Server/Instance/ServerInstance.hpp"

typedef std::bitset<5> t_mode;

class Server;
class Client;

class Channel {
	private:
		std::string					_name;
		std::vector<int>			_clients;
		std::vector<int>			_invited;
		std::vector<int>			_operators;
		std::vector<Message *>		_messages;
		t_mode						_mode;
		Server						*_server;
		std::string					_topic;

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
		bool						hasClient(Client client);
		void						showClients();
		void						kickClient(int fd);

		bool						removeClient(int fd);
		static void					removeClient(Channel *channel, int fd);

		static void					remove(Channel *channel);
		void						sendMessage(Client *sender, std::string message);


		bool						hasMode(t_mode mode);
		void						addMode(t_mode mode);
		void						delMode(t_mode mode);

		static Channel				*create(std::string name);

		bool						hasOperator(Client client);

		void						invite(Client client);
		bool						hasInvited(Client client);

		void						setTopic(std::string topic);
		std::string					getTopic();
};

std::iostream &operator<<(std::iostream &stream, Channel &client);

#endif