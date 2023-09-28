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
		_clients.insert(std::pair<int, Client>(newClient.fd, Client()));
		std::cout << "Nouveau client ajouté" << std::endl;
		Client::sendMessage(_clientSocket, ":server 001 <nick> :Welcome to the <network> Network, <nick>!<user>@<host>\r\n");
	}
}

void	Server::readClientInput(std::vector<pollfd>::iterator it, pollfd client)
{
	char buffer[1024] = {0};
	ssize_t bytesRead = read(client.fd, buffer, sizeof(buffer));
	buffer[bytesRead] = '\0';

	if (bytesRead <= 0) {
		this->disconnectClient(it);
	} else {
		this->parseInput(client.fd, buffer);
	}
}

void	Server::disconnectClient(std::vector<pollfd>::iterator it)
{
	close(it->fd);
	_pollfds.erase(it);
	std::cout << "Client déconnecté" << std::endl;
}

void	Server::parseInput(int fd, std::string input)
{
	(void) fd;
	std::string command = this->_parser->getCommand(input);
	std::vector<std::string> parameters = this->_parser->getParameters(input);

	if (!Auth::isAuthorized(this->_clients[fd], command))
			Client::sendMessage(fd, "You must be logged in to use this server\r\n");
	if (Auth::authenticate(this->_clients[fd], parameters[1]))
	{
		Client::sendMessage(_clientSocket, "Success\r\n");
	}
	else{
		Client::sendMessage(_clientSocket, "Failed\r\n");
	}
	// this->_parser->execute(command, parameters);
}

std::string Server::getPassword()
{
	return this->_password;
}

void	Server::stop(std::string message, int exitCode)
{
	close(this->_serverSocket);
	ServerInstance::destroyInstance();
	std::cout << "Server stopped" << std::endl;
	if (exitCode)
	{
		std::cerr << message << std::endl;
		exit(EXIT_FAILURE);
	}
}

Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
}

Server	&Server::operator=(const Server &copy)
{
	std::cout << "Server assignation operator called" << std::endl;
	if (this != &copy)
	{
		// Do stuff
	}
	return (*this);
}
