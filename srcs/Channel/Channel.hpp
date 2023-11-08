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
		std::string					_password;
		std::size_t					_limit;

	public:
		Channel();
		~Channel();
		Channel(const Channel &copy);

		enum Mode
		{
			BASE_MASK	= 31, //0b11111,
			I_INVITE	= 16, //0b10000,
			T_TOPIC		= 8, // 0b01000,
			K_PASSWORD	= 4, //0b00100,
			O_OPERATOR	= 2, //0b00010,
			L_LIMIT		= 1 //0b00001
		};

		std::string					getName();
		void						setName(std::string name);

		void						addClient(int fd);
		std::vector<int>			getClients();
		bool						hasClient(int fd);
		bool						hasClient(Client & client);
		void						showClients();
		void 						removeClient(int fd);

		void						broadcastMessage(Client *sender, const std::string& message);
		void						broadcastChanMsg(Client *sender, const std::string &message);

		bool						hasMode(t_mode mode);
		void						addMode(t_mode mode);
		void						delMode(t_mode mode);

		static Channel				*create(std::string name);

		std::vector<int>			getOperators();
		bool						hasOperator(Client client);
		void						addOperator(int fd);
		void						removeOperator(int fd);

		void						invite(Client client);
		void						removeInvited(Client client);
		void						removeInvited(int fd);
		bool						hasInvited(Client client);

		void						setTopic(std::string topic);
		std::string					getTopic();
		void						sendTopic();
		std::string					getNicknames();

		void						setPassword(std::string password);
		std::string					getPassword();
		bool						isPassword(std::string password);

		void						setLimit(std::size_t limit);
		std::size_t					getLimit();
		bool						isFull();

		bool						canJoin(Client &client);

		Channel						&operator=(const Channel &copy);
};

std::iostream &operator<<(std::iostream &stream, Channel &client);

#endif
