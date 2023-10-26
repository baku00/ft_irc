#include "Client.hpp"
#include "../Server/Instance/ServerInstance.hpp"
#include <string>

Client::Client() {
	throw std::runtime_error("Cannot create a client without a fd");
}

Client::Client(int fd) {
	this->_fd = fd;
	this->_isAuthenticated = false;
	this->_isValidate = false;

	// Here we should also set some other default values
	this->_nickname = "*";
}

Client::Client(const Client &copy) {
	*this = copy;
}

void Client::setNickname(std::string nickname) {
	this->_nickname = nickname;

	this->validate();
}

void Client::setUserInfo(std::string username, std::string hostname, std::string servername, std::string realname) {
	this->setUsername(username);
	this->setHostname(hostname);
	this->setServername(servername);
	this->setRealname(realname);

	this->validate();
}

void Client::setUsername(std::string username) {
	this->_username = username;

	if (!this->getNickname().length())
		this->setNickname(username);
}

void Client::setHostname(std::string hostname) {
	this->_hostname = hostname;
}

void Client::setServername(std::string serverName) {
	this->_serverName = serverName;
}

void Client::setRealname(std::string realName) {
	std::cout << "Real name: " << realName << std::endl;
	this->_realName = realName;
}

void Client::login(bool is_logged_in) {
	if (!this->isAuthenticated())
		this->_isAuthenticated = is_logged_in;
}

std::string Client::getNickname() {
	return this->_nickname;
}

std::string Client::getUsername() {
	return this->_username;
}

std::string Client::getHostname() {
	return this->_hostname;
}

std::string Client::getServername() {
	return this->_serverName;
}

std::string Client::getRealname() {
	std::cout << "_realName: " << this->_realName << std::endl;
	return this->_realName;
}

std::string Client::getInfo() {
	std::string info = "";

	info += "Nickname: " + this->getNickname() + "\r\n";
	info += "Username: " + this->getUsername() + "\r\n";
	info += "Hostname: " + this->getHostname() + "\r\n";
	info += "Realname: " + this->getRealname() + "\r\n";
	info += "Servername: " + this->getServername() + "\r\n";

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

std::string Client::getFullname() {
	return ":" + this->getNickname() + "!" + this->getUsername() + "@" + this->getHostname();
}

int Client::getFd() {
	return this->_fd;
}

bool Client::isAuthenticated() {
	return this->_isAuthenticated;
}

bool Client::isValidate() {
	this->validate();
	return this->_isValidate;
}

void Client::validate() {
	this->_isValidate = this->getNickname().length() && \
                        this->getNickname() != "*" && \
                        this->getUsername().length() && \
                        this->getHostname().length() && \
                        _isAuthenticated;
}

Client::~Client() {}

void Client::sendMessage(int socket, std::string message) {
	if (message.find("\r\n") == std::string::npos)
		message += "\r\n";

	std::cout << ">> " << message << std::endl;

	ssize_t bytesSent = send(socket, message.c_str(), message.length(), 0);

	if (bytesSent == -1) {
		std::cerr << "Erreur lors de l'envoi de la réponse au client." << std::endl;
	} else {
//		std::cout << "Réponse envoyé au client." << std::endl;
	}
}

void Client::sendMessage(Client *sender, std::string message) {
	if (sender == NULL)
		throw std::runtime_error("Sender can't be NULL");

	Client::sendMessage(this->getFd(), sender->getFullname() + " " + message);
}

void Client::sendPrivMsg(Client *sender, std::string message) {
	std::string privMsgPrefix = "PRIVMSG " + this->getNickname() + " :";
	this->sendMessage(sender, privMsgPrefix + message);
}

void Client::sendChanMsg(Client *sender, std::string channel, std::string message) {
	std::string chanMsgPrefix = "PRIVMSG " + channel + " :";
	this->sendMessage(sender, chanMsgPrefix + message);
}

void Client::reply(std::string code, std::string message...) {
	va_list args;
	va_start(args, message);

	std::size_t arg_pos = message.find("<");
	std::size_t end_pos = message.find(">");
	int length = end_pos - arg_pos + 1;

	while (arg_pos != std::string::npos && end_pos != std::string::npos) {
		if (length < 0)
			throw std::runtime_error(SSTR("Unexpected token '>' at column " << end_pos));

		char *replace = va_arg(args, char *);
		//std::cout << "REPLY: replace: " << replace << std::endl;
		message.replace(arg_pos, length, replace);

		arg_pos = message.find("<");
		end_pos = message.find(">");
		length = end_pos - arg_pos + 1;
	}

	va_end(args);

	std::string reply = ":" + this->getServername() + " " + code + " " + this->getNickname() + " " + message;
	//std::cout << reply << std::endl;
	sendMessage(this->getFd(), reply);
}

Client &Client::operator=(const Client &copy) {
	if (this != &copy) {
		this->_nickname = copy._nickname;
		this->_username = copy._username;
		this->_hostname = copy._hostname;
		this->_serverName = copy._serverName;
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
