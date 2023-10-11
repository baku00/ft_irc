#include "Server.hpp"

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
	this->_parser = new Parser();
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

	this->createSocket();

	serverAddr = this->fixSettings();

	this->linkSocketToPort(serverAddr);
	this->startListening();
	this->initialiseConnection();
	this->loop(clientAddr, clientAddrLen);
	this->stop("Server stopped", 0);
}

void	Server::createSocket()
{
	this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_serverSocket == -1) {
		this->stop("Erreur lors de la création du socket.", EXIT_FAILURE);
	}
}

sockaddr_in	Server::fixSettings()
{
	struct sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(this->_port);

	return serverAddr;
}

void	Server::linkSocketToPort(sockaddr_in serverAddr)
{
	if (bind(this->_serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
		this->stop("Erreur lors de la liaison du socket au port.", EXIT_FAILURE);
	}
}

void	Server::startListening()
{
	if (listen(this->_serverSocket, 5) == -1) {
		this->stop("Erreur lors de l'attente de connexions entrantes.", EXIT_FAILURE);
	}
	std::cout << "Serveur IRC en attente de connexions sur le port " << this->_port << std::endl;
}

void	Server::initialiseConnection()
{
	this->_pollfds[0].fd = this->_serverSocket;
	this->_pollfds[0].events = POLLIN;

	std::cout << "Prêts à être connecté" << std::endl;
}

void	Server::loop(sockaddr_in clientAddr, socklen_t clientAddrLen)
{
	while (true) {
		this->waitForIncomingConnection();

		for (size_t i = 0; i < this->_pollfds.size(); i++)
		{
			if (this->_pollfds[i].revents & POLLIN)
			{
				if (i == 0)
					this->acceptNewConnection(clientAddr, clientAddrLen);
				else
					this->readClientInput(this->_pollfds.begin() + i, this->_pollfds[i]);
			}
		}
	}
}

void	Server::waitForIncomingConnection()
{
	std::cout << "Attente de connexions entrantes..." << std::endl;

	int numReady = poll(this->_pollfds.data(), this->_pollfds.size(), -1);

	if (numReady == -1) {
		this->stop("Erreur lors de l'appel à poll().", EXIT_FAILURE);
	}
}

void	Server::acceptNewConnection(sockaddr_in clientAddr, socklen_t clientAddrLen)
{
	_clientSocket = accept(this->_serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
	if (_clientSocket == -1) {
		std::cerr << "Erreur lors de l'acceptation de la connexion." << std::endl;
	} else {
		struct pollfd newClient;
		newClient.fd = _clientSocket;
		newClient.events = POLLIN;
		_pollfds.push_back(newClient);
		_clients.insert(std::pair<int, Client>(newClient.fd, Client(newClient.fd, true)));
		std::cout << "Nouveau client ajouté" << std::endl;
		Client::sendMessage(_clientSocket, ":server 001 <nick> :Welcome to the <network> Network, <nick>!<user>@<host>\r\n");
	}
}

void	Server::readClientInput(std::vector<pollfd>::iterator it, pollfd client)
{
	char buffer[1024] = {0};
	ssize_t bytesRead = read(client.fd, buffer, sizeof(buffer));
	buffer[bytesRead] = '\0';
	std::cout << "Buffer:" << std::endl;
	std::cout << "(" << buffer << ")" << std::endl;
	if (bytesRead <= 0) {
		this->disconnectClient(it);
	} else {
		this->parseInput(client.fd, buffer);
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
		this->disconnectClient(it);
}

void	Server::disconnectClient(std::vector<pollfd>::iterator it)
{
	close(it->fd);
	_pollfds.erase(it);
	_clients.erase(it->fd);
	std::cout << "Client déconnecté" << std::endl;
}

void	Server::parseInput(int fd, std::string input)
{
	Client &client = this->_clients[fd];

	// TODO: buffer
	// if input doesnt end with \r\n: 
	// 		put command into client buffer

	size_t new_line;
	while ((new_line = input.find("\r\n")) != std::string::npos)
	{
		std::string line = input.substr(0, new_line);
		input = input.substr(new_line + 2);

		std::string command				= this->_parser->getCommand(line);
		std::vector<std::string> args	= this->_parser->getParameters(line);

		// if (!Auth::isAuthorized(client, command))
		// 	Client::sendMessage(fd, "Vous devez être connecté au serveur et avoir un compte valide\r\n");
		// else
			this->_parser->execute(client, command, args);
	}
}

std::string Server::getPassword()
{
	return this->_password;
}

Client	*Server::getClient(int fd)
{
	return &this->_clients[fd];
}

Client	*Server::getClientByNickname(std::string nickname)
{
	for (std::map<int, Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (it->second.getNickname() == nickname)
			return &it->second;
	}
	std::cout << "Nothing client found" << std::endl;
	return NULL;
}

Client	*Server::getClientByServername(std::string servername)
{
	for (std::map<int, Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (it->second.getServername() == servername)
			return &it->second;
	}
	return NULL;
}

Client	*Server::getClientByHostname(std::string hostname)
{
	for (std::map<int, Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
	{
		if (it->second.getHostname() == hostname)
			return &it->second;
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

void	Server::stop(std::string message, int exitCode)
{
	close(this->_serverSocket);
	ServerInstance::destroyInstance();
	std::cout << "Server stopped" << std::endl;
	if (exitCode)
	{
		std::cerr << message << std::endl;
		exit(exitCode);
	}
}

Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
}

Server	&Server::operator=(const Server &copy)
{
	(void) copy;
	std::cout << "Server assignation operator called" << std::endl;
	return (*this);
}

const char			*Server::ChannelNotFoundException::what() const throw()
{
	return ("Channel not found");
}

const char			*Server::ChannelAlreadyExist::what() const throw()
{
	return ("Channel already exist");
}