#include "Channel.hpp"
#include "Mode/Mode.hpp"

Channel::Channel()
{
	this->_name = "";
	this->_topic = "";
	this->_mode = new Mode();
}

Channel::Channel(std::string name, bool by_name) {
	(void) by_name;
	this->_name = name;
}

Channel::Channel(const Channel &copy) {
	*this = copy;
}

Channel::~Channel() {
	delete this->_mode;
}

Channel &Channel::operator=(const Channel &copy) {
	if (this != &copy) {
		this->_name = copy._name;
	}
	return *this;
}

std::string	Channel::getName() {
	return this->_name;
}

Mode	&Channel::mode()
{
	return *this->_mode;
}