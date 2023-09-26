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
}

Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
}

Server::Server(const Server &copy)
{
	std::cout << "Server copy constructor called" << std::endl;
	*this = copy;
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

void	Server::sendWelcomeMessage(int clientSocket)
{
	std::string welcomeMessage = "Welcome to the IRC server! You are now connected.\r\n";
	
	// Envoi du message au client
	ssize_t bytesSent = send(clientSocket, welcomeMessage.c_str(), welcomeMessage.length(), 0);
	
	if (bytesSent == -1) {
		std::cerr << "Erreur lors de l'envoi du message de bienvenue au client." << std::endl;
	} else {
		std::cout << "Message de bienvenue envoyé au client." << std::endl;
	}
}

void	Server::start()
{
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);

	// Création du socket du serveur
	this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_serverSocket == -1) {
		std::cerr << "Erreur lors de la création du socket." << std::endl;
		exit(EXIT_FAILURE);
	}

	// Configuration des paramètres du serveur
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(this->_port);

	// Liaison du socket au port
	if (bind(this->_serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
		std::cerr << "Erreur lors de la liaison du socket au port." << std::endl;
		close(this->_serverSocket);
		exit(EXIT_FAILURE);
	}

	// Attente de connexions entrantes
	if (listen(this->_serverSocket, 5) == -1) {
		std::cerr << "Erreur lors de l'attente de connexions entrantes." << std::endl;
		close(this->_serverSocket);
		exit(EXIT_FAILURE);
	}

	std::cout << "Serveur IRC en attente de connexions sur le port " << this->_port << std::endl;

	std::vector<struct pollfd> clients(1024);
	clients[0].fd = this->_serverSocket;
	clients[0].events = POLLIN;

	std::cout << "Prêts à être connecté" << std::endl;

	while (true) {
		std::cout << "Attente de connexions entrantes..." << std::endl;
		int numReady = poll(clients.data(), clients.size(), -1); // -1 signifie une attente indéfinie

		if (numReady == -1) {
			std::cerr << "Erreur lors de l'appel à poll()." << std::endl;
			exit(EXIT_FAILURE);
		}

		std::cout << "Client size " << clients.size() << std::endl;

		for (size_t i = 0; i < clients.size(); ++i) {
			if (clients[i].revents & POLLIN) {
				if (i == 0) {
					// Nouvelle connexion entrante sur le socket du serveur
					_clientSocket = accept(this->_serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
					if (_clientSocket == -1) {
						std::cerr << "Erreur lors de l'acceptation de la connexion." << std::endl;
					} else {
						// Ajouter le nouveau client au tableau clients
						struct pollfd newClient;
						newClient.fd = _clientSocket;
						newClient.events = POLLIN;
						clients.push_back(newClient);
						std::cout << "Nouveau client ajouté" << std::endl;
						sendWelcomeMessage(_clientSocket);
					}
				} else {
					// Données disponibles à lire sur un client existant
					// Ici, vous devrez gérer la lecture des données du client
					char buffer[1024];
					ssize_t bytesRead = recv(clients[i].fd, buffer, sizeof(buffer), 0);
					if (bytesRead <= 0) {
						// Le client a fermé la connexion ou une erreur s'est produite
						close(clients[i].fd);
						clients.erase(clients.begin() + i);
						std::cout << "Client déconnecté" << std::endl;
					} else {
						// Traitez les données lues depuis le client ici
						// buffer contient les données lues
						std::cout << "Received" << std::endl;
					}
				}
			}
		}
	}

	// Fermer le socket du serveur (ce code ne sera jamais atteint dans cette boucle infinie)
	close(this->_serverSocket);
}