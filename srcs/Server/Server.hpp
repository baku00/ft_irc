#ifndef SERVER_HPP
# define SERVER_HPP

# include <main.hpp>
# include "../Client/Client.hpp"
# include "../Parser/Parser.hpp"
# include "../Auth/Auth.hpp"
# include "../Channel/Channel.hpp"

class Parser;
class Channel;

class Server
{
	private:
		int									_port;
		std::string							_password;
		int									_serverSocket;
		int									_clientSocket;
		std::vector<struct pollfd>			_pollfds;
		std::map<std::string, Channel *>	_channels;
		std::map<int, Client *>				_clients;
		std::map<int, Client *>				_connections;
		std::string							_server_name;
        std::string                         _version;
        std::string                         _created_at;
		Parser								*_parser;
		bool								_is_started;

		Server();

		void								_createSocket();
		void								_linkSocketToPort(sockaddr_in serverAddr);
		void								_startListening();
		void								_initialiseConnection();
		void								_loop(sockaddr_in clientAddr, socklen_t clientAddrLen);
		void								_waitForIncomingConnection();
		void								_acceptNewConnection(sockaddr_in clientAddr, socklen_t clientAddrLen);
		void								_parseInput(int fd, std::string input);
		void								_readClientInput(std::vector<pollfd>::iterator it, pollfd client);
		void								_disconnectClient(std::vector<pollfd>::iterator it);
		void								_deleteChannels();
		void								_deleteClients();
		void								_deleteConnections();
		void								_deleteParser();
		void								_forceDisconnect(int fd);
		void								_disconnectFromConnections(int fd);
		void								_disconnectFromClients(int fd);
		void								_disconnectFromChannels(int fd);

		static Client						*_getByFd(int fd, std::map<int, Client *> & clients);


		sockaddr_in							_fixSettings();

	public:
		Server(int port, std::string password);
		~Server();
		Server(const Server &copy);
		Server								&operator=(const Server &copy);

		std::string							getPassword();

		Client								*getClient(int fd);
        Client                              *getConnection(int fd);

		Client								*getClientByNickname(std::string nickname);

		void								addChannel(Channel *channel);
		Channel								*getChannel(std::string name);
		std::map<std::string, Channel *>	getChannels();

		void								broadcastMessage(Client *sender, const std::string& message);

		void								disconnectClientFromFD(int fd);

		void								start();
		void								stop(std::string message, int exitCode);

		class ChannelNotFoundException : public std::exception
		{
			virtual const char *what() const throw();
		};

		class ChannelAlreadyExist : public std::exception
		{
			virtual const char *what() const throw();
		};

        class ClientNotFoundException : public std::exception
        {
            public:
            virtual const char *what() const throw();
        };
};

#endif
