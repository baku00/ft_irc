#include "Client.hpp"

Client::Client()
{
	this->_isAuthenticated = false;
}

Client::Client(int fd) {
	this->_fd = fd;
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

void	Client::setCommand(std::string command) {
	this->_command = command;
}

void	Client::setArgs(std::vector<std::string> args) {
	this->_args = args;
}

std::string	Client::getCommand() {
	return this->_command;
}

std::vector<std::string>	Client::getArgs() {
	return this->_args;
}

std::string	Client::getNickname() {
	return this->_nickname;
}

std::string	Client::getUsername() {
	return this->_username;
}

int	Client::getFd() {
	return this->_fd;
}

bool	Client::isAuthenticated() {
	return this->_isAuthenticated;
}

Client::~Client() {
}

void	Client::sendMessage(int socket, std::string message)
{
	if (message.find("\r\n") == std::string::npos)
		message += "\r\n";
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
		this->_fd = copy._fd;
	}
	return *this;
}