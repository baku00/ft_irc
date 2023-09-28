#include "Client.hpp"

Client::Client() {
	this->_isAuthenticated = false;
}

Client::Client(const Client &copy) {
	*this = copy;
}

void	Client::setNickname(std::string nickname) {
	this->_nickname = nickname;
}

void	Client::setUsername(std::string username) {
	this->_username = username;
}

void	Client::login(bool is_logged_in) {
	this->_isAuthenticated = is_logged_in;
}

std::string	Client::getNickname() {
	return this->_nickname;
}

std::string	Client::getUsername() {
	return this->_username;
}

bool	Client::isAuthenticated() {
	return this->_isAuthenticated;
}

Client::~Client() {
}

void	Client::sendMessage(int socket, std::string message)
{
	ssize_t bytesSent = send(socket, message.c_str(), message.length(), 0);
	if (bytesSent == -1) {
		std::cerr << "Erreur lors de l'envoi de la réponse au client." << std::endl;
	} else {
		std::cout << "Réponse envoyé au client." << std::endl;
	}
}

Client &Client::operator=(const Client &copy) {
	if (this != &copy) {
		this->_nickname = copy._nickname;
		this->_username = copy._username;
		this->_isAuthenticated = copy._isAuthenticated;
	}
	return *this;
}