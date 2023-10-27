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
		std::map<int, Client>				_clients;
		std::string							_server_name;
		Parser								*_parser;

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
		void								_deleteParser();
		void								_delete();

		sockaddr_in							_fixSettings();

	public:
		Server(int port, std::string password);
		~Server();
		Server(const Server &copy);
		Server								&operator=(const Server &copy);

		std::string							getPassword();

		Client								*getClient(int fd);
		Client								*getClientByNickname(std::string nickname);
		Client								*getClientByServername(std::string servername);
		Client								*getClientByHostname(std::string hostname);

		void								addChannel(Channel *channel);
		Channel								*getChannel(std::string name);
		std::map<std::string, Channel *>	getChannels();
		void		                        removeChannel(std::string name);

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
};

std::iostream &operator<<(std::iostream &stream, Server &server);

#endif
