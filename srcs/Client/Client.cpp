#include "Client.hpp"

Client::Client()
{
	this->_isAuthenticated = false;
	this->_isValidate = false;

}

Client::Client(int fd, bool by_fd) {
	(void) by_fd;
	this->_fd = fd;
	this->_isAuthenticated = false;
	this->_isValidate = false;

}

Client::Client(const Client &copy) {
	*this = copy;
}

void	Client::setNickname(std::string nickname) {
	if (!this->isValidNickname(nickname))
		return Client::sendMessage(this->getFd(), "432 " + this->getCommand() + " :Invalid nickname");

	this->_nickname = nickname;

	this->validate();
}

void	Client::setUserInfo(std::string username, std::string firstname, std::string lastname) {
	this->setUsername(username);
	this->setFirstname(firstname);
	this->setLastname(lastname);

	this->validate();
}

void	Client::setUsername(std::string username) {
	this->_username = username;

	if (!this->getNickname().length())
		this->setNickname(username);
}

void	Client::setFirstname(std::string firstname) {
	this->_firstname = firstname;
}

void	Client::setLastname(std::string lastname) {
	this->_lastname = lastname;
}

void	Client::login(bool is_logged_in) {
	if (!this->isAuthenticated())
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

std::string	Client::getFirstname() {
	return this->_firstname;
}

std::string	Client::getLastname() {
	return this->_lastname;
}

std::string	Client::getInfo() {
	std::string info = "";

	info += "Nickname: " + this->getNickname() + "\r\n";
	info += "Username: " + this->getUsername() + "\r\n";
	info += "Firstname: " + this->getFirstname() + "\r\n";
	info += "Lastname: " + this->getLastname() + "\r\n";

	if (this->isAuthenticated())
		info += "Is authenticated: Oui\r\n";
	else
		info += "Is authenticated: Non\r\n";

	if (this->isValidate())
		info += "Is validate: Oui\r\n";
	else
		info += "Is validate: Non\r\n";

	return info;
}

int	Client::getFd() {
	return this->_fd;
}

bool	Client::isAuthenticated() {
	return this->_isAuthenticated;
}

bool	Client::isValidate() {
	return this->_isValidate;
}

bool	Client::isValidNickname(std::string nickname) {
	if (!nickname.length())
		return false;
	if (nickname[0] == '#')
		return false;
	if (nickname.find(" ") != std::string::npos)
		return false;
	if (nickname.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != std::string::npos)
		return false;
	return true;
}

void	Client::validate() {
	// this->_isValidate = this->getNickname().length() && this->getUsername().length() && this->getFirstname().length() && this->getLastname().length();
	this->_isValidate = true;
}

Client::~Client() {}

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
		this->_isValidate = copy._isValidate;
	}
	return *this;
}

std::iostream &operator<<(std::iostream &stream, Client &client) {
	stream << client.getInfo();
	return stream;
}
