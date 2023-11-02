#include "Message.hpp"

Message::Message() {
	this->setSender(-1);
	this->setFullname("");
	this->setContent("");
}

Message::Message(int sender, std::string fullname, std::string content) {
	this->setSender(sender);
	this->setFullname(fullname);
	this->setContent(content);
}

Message::Message(const Message &copy) {
	*this = copy;
}

Message::~Message() {}

Message	&Message::operator=(const Message &copy) {
	if (this != &copy) {
		this->_sender = copy._sender;
		this->_content = copy._content;
	}
	return *this;
}

int			Message::getSender() const {
	return this->_sender;
}

std::string	Message::getFullname() const {
	return this->_fullname;
}

std::string	Message::getContent() const {
	return this->_content;
}

void		Message::setSender(int sender) {
	this->_sender = sender;
}

void		Message::setFullname(std::string fullname) {
	this->_fullname = std::string(fullname);
}

void		Message::setContent(std::string content) {
	this->_content = content;
}
