#include "Server.hpp"
#include <rpl_numeric.h>
#include <rpl_errors.h>

Server::Server()
{
	std::cout << "Default Server constructor called" << std::endl;
}

Server::Server(int port, std::string password)
{
	std::cout << "Server constructor called" << std::endl;
	this->_port = port;
	this->_password = password;
	this->_pollfds = std::vector<struct pollfd>(1);
	this->_server_name = "42IRC";
	this->_version = "1.0";
	this->_created_at = "2023";
	this->_parser = new Parser();
	this->_is_started = true;
}

Server::Server(const Server &copy)
{
	std::cout << "Server copy constructor called" << std::endl;
	*this = copy;
}

void	Server::start()
{
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);

	this->_createSocket();

	serverAddr = this->_fixSettings();

	this->_linkSocketToPort(serverAddr);
	this->_startListening();
	this->_initialiseConnection();
	this->_loop(clientAddr, clientAddrLen);
	this->stop("Server stopped", 0);
}

void	Server::_createSocket()
{
	this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_serverSocket == -1) {
		this->stop("Erreur lors de la création du socket.", EXIT_FAILURE);
	}
	int reuse = 1;
	if (setsockopt(this->_serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
		std::cerr << "Error failed to set SO_REUSEADDR" << std::endl;
		close(this->_serverSocket);
		return ;
	}

	// Set the socket to non-blocking mode
	if (fcntl(this->_serverSocket, F_SETFL, O_NONBLOCK) < 0) {
		std::cerr << "Error setting socket to non-blocking mode" << std::endl;
		close(this->_serverSocket);
		return;
	}
}

sockaddr_in	Server::_fixSettings()
{
	struct sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(this->_port);

	return serverAddr;
}

void	Server::_linkSocketToPort(sockaddr_in serverAddr)
{
	if (bind(this->_serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
		this->stop("Erreur lors de la liaison du socket au port.", EXIT_FAILURE);
	}
}

void	Server::_startListening()
{
	if (listen(this->_serverSocket, 5) == -1) {
		this->stop("Erreur lors de l'attente de connexions entrantes.", EXIT_FAILURE);
	}
	std::cout << "Serveur IRC en attente de connexions sur le port " << this->_port << std::endl;
}

void	Server::_initialiseConnection()
{
	this->_pollfds[0].fd = this->_serverSocket;
	this->_pollfds[0].events = POLLIN;

	std::cout << "Prêts à être connecté" << std::endl;
}

void	Server::_loop(sockaddr_in clientAddr, socklen_t clientAddrLen)
{
	while (this->_is_started) {
		for (size_t i = 0; i < 10; i++)
			std::cout << std::endl;
		std::cout << "Wait of connection" << std::endl;
		this->_waitForIncomingConnection();

		for (size_t i = 0; this->_is_started && i < this->_pollfds.size(); i++)
		{
			std::cout << "Check fd" << std::endl;
			if (this->_pollfds[i].revents & POLLIN)
			{
				if (i == 0)
					this->_acceptNewConnection(clientAddr, clientAddrLen);
				else
					this->_readClientInput(this->_pollfds.begin() + i, this->_pollfds[i]);
				std::cout << "End check fd" << std::endl;
			}
			if (!this->_is_started)
			{
				std::cout << "Stopping for" << std::endl;
				break;
			}
			std::cout << "Out of check" << std::endl;
		}
		std::cout << "Restarting while" << std::endl;
	}
	std::cout << "While stopped" << std::endl;
}

void	Server::_waitForIncomingConnection()
{
	std::cout << "Attente de connexions entrantes..." << std::endl;

	int numReady = poll(this->_pollfds.data(), this->_pollfds.size(), -1);

	if (numReady == -1) {
		this->stop("Erreur lors de l'appel à poll().", EXIT_FAILURE);
	}
}

void	Server::_acceptNewConnection(sockaddr_in clientAddr, socklen_t clientAddrLen)
{
	_clientSocket = accept(this->_serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
	if (_clientSocket == -1) {
		std::cerr << "Erreur lors de l'acceptation de la connexion." << std::endl;
	} else {
		struct pollfd newClient;
		newClient.fd = _clientSocket;
		newClient.events = POLLIN;
		_pollfds.push_back(newClient);

		Client * client = new Client(newClient.fd);
		_connections.insert(std::pair<int, Client *>(newClient.fd, client));
		std::cout << "Nouvelle connection" << std::endl;
	}
}

void	Server::_readClientInput(std::vector<pollfd>::iterator it, pollfd client)
{
	char buffer[1024] = {0};
	std::cout << "Client fd: " << client.fd << std::endl;
	ssize_t bytesRead = read(client.fd, buffer, sizeof(buffer));
	std::cout << "bytesRead: " << bytesRead << std::endl;
	if (bytesRead <= 0) {
		this->_disconnectClient(it);
	} else {
		Client *_client = this->getClient(client.fd);
		if (!_client)
			_client = this->getConnection(client.fd);
		buffer[bytesRead] = '\0';
		std::cout << "Client: " << _client << std::endl;
		if (!_client)
			return;
		_client->addInput(buffer);
		this->_parseInput(client.fd, _client->getInput());
	}
}

void	Server::disconnectClientFromFD(int fd)
{
	std::vector<pollfd>::iterator it = this->_pollfds.begin();
	for (; it != this->_pollfds.end(); it++)
	{
		if (it->fd == fd)
			break;
	}
	if (it != this->_pollfds.end())
		this->_disconnectClient(it);
}

void	Server::_disconnectClient(std::vector<pollfd>::iterator it)
{
	std::cout << "Déconnexion du client" << std::endl;
	std::cout << "FD: " << it->fd << std::endl;
	this->_forceDisconnect(it->fd);
	_pollfds.erase(it);
	std::cout << "Client déconnecté" << std::endl;
}

void	Server::_disconnectFromChannels(int fd)
{
	std::map<std::string, Channel *>::iterator	channel;
	if (this->_channels.size() > 0)
		for (channel = this->_channels.begin(); channel != this->_channels.end(); channel++)
			channel->second->removeClient(fd);
}

void	Server::_disconnectFromClients(int fd)
{
	for (std::map<int, Client *>::iterator client = _clients.begin(); client != _clients.end(); client++)
	{
		if (client->second->getFd() == fd)
			delete client->second;
	}
	if (_clients.size() > 1)
		_clients.erase(fd);
	else
		_clients.clear();
}

void	Server::_disconnectFromConnections(int fd)
{
	for (std::map<int, Client *>::iterator connection = _connections.begin(); connection != _connections.end(); connection++)
	{
		if (connection->second->getFd() == fd)
			delete connection->second;
	}
	if (_connections.size() > 1)
		_connections.erase(fd);
	else
		_connections.clear();
}

void	Server::_forceDisconnect(int fd)
{
	this->_disconnectFromClients(fd);
	this->_disconnectFromConnections(fd);
	this->_disconnectFromChannels(fd);
	close(fd);
}

void	Server::_parseInput(int fd, std::string input)
{
	for (size_t i = 0; i < input.length(); i++)
		std::cout << i << ": [" << static_cast<int>(input[i]) << "]" << std::endl;

	if (input.find("\r\n") == std::string::npos)
		return;
	Client * client;
	bool is_registered = false;
	client = this->getClient(fd);
	if (client)
		is_registered = true;
	else
		client = this->getConnection(fd);

	if (!client)
	{
		this->_forceDisconnect(fd);
		std::cerr << "Client not found" << std::endl;
		return ;
	}
	// TODO: buffer
	// if input doesnt end with \r\n: 
	// 		put command into client buffer

	size_t new_line;
	size_t pos = input.find_last_of("\r\n");
	if (pos == std::string::npos)
	{
		pos = input.find_last_of("\n");
		input.replace(pos, 1, "\r\n");
	}
	while ((new_line = input.find("\r\n")) != std::string::npos)
	{
		std::string line = input.substr(0, new_line);
		std::cout << "<< " << line << std::endl;
		input = input.substr(new_line + 2);

		// std::string channel				= this->_parser->getChannel(line);
		std::string command				= Parser::getCommand(line);
		std::vector<std::string> args	= Parser::getParameters(line);

		if (Auth::isAuthorized(command, is_registered))
			this->_parser->execute(*client, command, args);
		else
			client->reply(ERR_RESTRICTED);

		for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); it++)
		{
			it->clear();
		}
		args.clear();
		command.clear();
	}

	if (!is_registered && client->isValidate())
	{
		_clients.insert(std::pair<int, Client *>(fd, client));
		_connections.erase(fd);

		client->reply(RPL_WELCOME,
					client->getNickname().c_str(),
					client->getUsername().c_str(),
					client->getHostname().c_str());
		client->reply(RPL_YOURHOST,
					this->_server_name.c_str(),
					this->_version.c_str());
		client->reply(RPL_CREATED,
					this->_created_at.c_str());
		client->reply(RPL_MYINFO,
					this->_server_name.c_str(),
					this->_version.c_str(),
					"*", "{[+|-]|i|t|k|o|l}");
	}
	client->clearInput();
}

std::string Server::getPassword()
{
	return this->_password;
}

Client  *Server::_getByFd(int fd, std::map<int, Client *> & clients) {
	std::map<int, Client *>::iterator client_iter = clients.find(fd);
	if (client_iter == clients.end())
		return NULL;
	Client * client = client_iter->second;
	return client;
}

Client	*Server::getClient(int fd)
{
	// WARNING: if the client does not exist,
	//          a new one will be added.
	// return &this->_clients[fd];

	// Better do this:
	return _getByFd(fd, this->_clients);
	

	// Which is something like this:
//    std::map<int, Client *>::iterator client_iter = this->_clients.find(fd);
//    if (client_iter == this->_clients.end())
//        throw ClientNotFoundException();
//    Client * client = client_iter->second;
//    return client;
}

Client	*Server::getConnection(int fd)
{
	try
	{
		return _getByFd(fd, this->_connections);
	}
	catch(const std::exception& e)
	{
		return NULL;
	}
	
}

Client	*Server::getClientByNickname(std::string nickname)
{
	for (std::map<int, Client *>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (it->second->getNickname() == nickname)
			return it->second;
	}
	return NULL;
}

void	Server::addChannel(Channel *channel)
{
	if (!this->getChannel(channel->getName()))
		this->_channels.insert(std::pair<std::string, Channel *>(channel->getName(), channel));
}

Channel	*Server::getChannel(std::string name)
{
	std::map<std::string, Channel *>::iterator it = this->_channels.find(name);

	if (it == this->_channels.end())
		return NULL;
	return it->second;
}

std::map<std::string, Channel *>	Server::getChannels()
{
	return this->_channels;
}

void	Server::stop(std::string message, int exitCode)
{
	this->_is_started = false;
	this->_deleteConnections();
	this->_deleteChannels();
	this->_deleteClients();
	this->_deleteParser();
	std::cout << "Server stopped" << std::endl;
	if (exitCode)
		std::cerr << message << std::endl;
	exit(exitCode);
}

Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
	this->stop("", 0);
}

void	Server::_deleteParser()
{
	std::cout << "Destruction du parser" << std::endl;
	delete this->_parser;
}

void	Server::_deleteConnections()
{
	std::cout << "Destruction des connexions" << std::endl;
	std::map<int, Client *>::iterator it;
	for (it = this->_connections.begin(); it != this->_connections.end(); it++)
		delete it->second;
}

void	Server::_deleteChannels()
{
	std::cout << "Destruction des channels" << std::endl;
	std::map<std::string, Channel *>::iterator it;
	for (it = this->_channels.begin(); it != this->_channels.end(); it++)
		delete it->second;
}

void	Server::_deleteClients()
{
	std::cout << "Destruction des clients" << std::endl;
	std::map<int, Client *>::iterator it;
	for (it = this->_clients.begin(); it != this->_clients.end(); it++)
		delete it->second;
}

Server	&Server::operator=(const Server &copy)
{
	(void) copy;
	std::cout << "Server assignation operator called" << std::endl;
	return (*this);
}

void Server::broadcastMessage(Client *sender, const std::string &message)
{
	std::map<int, Client *>::iterator  client;
	for (client = _clients.begin(); client != _clients.end(); client++)
		client->second->sendMessage(sender, message);
}

const char			*Server::ChannelNotFoundException::what() const throw()
{
	return ("Channel not found");
}

const char			*Server::ChannelAlreadyExist::what() const throw()
{
	return ("Channel already exist");
}

const char *Server::ClientNotFoundException::what() const throw() {
	return ("Client does not exist");
}
