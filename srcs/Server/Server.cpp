#include "Server.hpp"

Server::Server()
{
	std::cout << "Server constructor called" << std::endl;
}

Server::Server(int port, std::string password)
{
	std::cout << "Server constructor called" << std::endl;
	this->_port = port;
	this->_password = password;
	this->_pollfds = std::vector<struct pollfd>(1);
	this->_server_name = "42IRC";
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
	// Création du socket du serveur
	this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_serverSocket == -1) {
		this->stop("Erreur lors de la création du socket.", EXIT_FAILURE);
	}
}

sockaddr_in	Server::fixSettings()
{
	struct sockaddr_in serverAddr;

	// Configuration des paramètres du serveur
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(this->_port);

	return serverAddr;
}

void	Server::linkSocketToPort(sockaddr_in serverAddr)
{
	// Liaison du socket au port
	if (bind(this->_serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
		this->stop("Erreur lors de la liaison du socket au port.", EXIT_FAILURE);
	}
}

void	Server::startListening()
{
	// Attente de connexions entrantes
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

	int numReady = poll(this->_pollfds.data(), this->_pollfds.size(), -1); // -1 signifie une attente indéfinie

	if (numReady == -1) {
		this->stop("Erreur lors de l'appel à poll().", EXIT_FAILURE);
	}
}

void	Server::acceptNewConnection(sockaddr_in clientAddr, socklen_t clientAddrLen)
{
	// Nouvelle connexion entrante sur le socket du serveur
	_clientSocket = accept(this->_serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
	if (_clientSocket == -1) {
		std::cerr << "Erreur lors de l'acceptation de la connexion." << std::endl;
	} else {
		// Ajouter le nouveau client au tableau _pollfds
		struct pollfd newClient;
		newClient.fd = _clientSocket;
		newClient.events = POLLIN;
		_pollfds.push_back(newClient);
		_clients.insert(std::pair<int, Client>(newClient.fd, Client()));
		std::cout << "Nouveau client ajouté" << std::endl;
		sendWelcomeMessage(_clientSocket);
	}
}

void	Server::readClientInput(std::vector<pollfd>::iterator it, pollfd client)
{
	char buffer[1024] = {0};
	ssize_t bytesRead = read(client.fd, buffer, sizeof(buffer));
	if (bytesRead <= 0) {
		this->disconnectClient(it);
	} else {
		// if (!Auth::isAuthorized(this->_clients[client.fd], buffer))
		// {
		// 	Auth::sendError(client.fd, buffer);
		// }
		// if (Auth::isAuthenticated(client.fd) == false)
		// {
		// 	Auth::login(client.fd, buffer);
		// }
		// else
		// {
		// 	// Ici, vous devrez gérer la lecture des données du client
		// 	this->parseInput(client.fd, buffer);
		// }
		//this->parseInput(client.fd, buffer);
		std::cout << "Message from " << client.fd << " in buffer " << buffer << std::endl;
	}
}

void	Server::sendWelcomeMessage(int clientSocket)
{
	std::string welcomeMessage = ":server 001 <nick> :Welcome to the <network> Network, <nick>!<user>@<host>\r\n";
	
	// Envoi du message au client
	ssize_t bytesSent = send(clientSocket, welcomeMessage.c_str(), welcomeMessage.length(), 0);
	
	if (bytesSent == -1) {
		std::cerr << "Erreur lors de l'envoi du message de bienvenue au client." << std::endl;
	} else {
		std::cout << "Message de bienvenue envoyé au client." << std::endl;
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
	std::cout << "Received" << std::endl;
	std::cout << "(" << input << ")" << std::endl;
	std::cout << "Command: " << Parser::getCommand(input) << std::endl;
	std::cout << "Parameters: " << std::endl;
	std::vector<std::string> parameters = Parser::getParameters(input);
	for (size_t i = 0; i < parameters.size(); i++)
	{
		std::cout << "\t" << i << "." << parameters[i] << std::endl;
	}
	std::cout << std::endl;
	// std::cout << "Is Authenticated: " << this->_clients[fd].isAuthenticated() << std::endl;
}

void	Server::stop(std::string message, int exitCode)
{
	close(this->_serverSocket);
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
