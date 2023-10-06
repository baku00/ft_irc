#ifndef SERVER_HPP
# define SERVER_HPP

# include <main.hpp>
# include "../Client/Client.hpp"
# include "../Parser/Parser.hpp"
# include "../Auth/Auth.hpp"

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
		std::map<int, Client>				_clients;
		std::string							_server_name;
		Parser								*_parser;

		Server();

		void		createSocket();
		sockaddr_in	fixSettings();
		void		linkSocketToPort(sockaddr_in serverAddr);
		void		startListening();
		void		initialiseConnection();
		void		loop(sockaddr_in clientAddr, socklen_t clientAddrLen);
		void		managePoll();
		void		managePollError(int clientSocket);
		void		managePollInput(int clientSocket);
		void		managePollOutput(int clientSocket);
		void		managePollOutputError(int clientSocket);
		void		waitForIncomingConnection();
		void		acceptNewConnection(sockaddr_in clientAddr, socklen_t clientAddrLen);
		void		parseInput(int fd, std::string input);
		void		readClientInput(std::vector<pollfd>::iterator it, pollfd client);
		void		disconnectClient(std::vector<pollfd>::iterator it);

	public:
		Server(int port, std::string password);
		~Server();
		Server(const Server &copy);
		Server		&operator=(const Server &copy);

		std::string	getPassword();

		Client		*getClient(int fd);
		Client		*getClientByNickname(std::string nickname);
		Client		*getClientByServername(std::string servername);
		Client		*getClientByHostname(std::string hostname);

		void		disconnectClientFromFD(int fd);

		void		start();
		void		stop(std::string message, int exitCode);

		class ChannelNotFoundException : public std::exception
		{
			virtual const char *what() const throw();
		};
};

#endif
