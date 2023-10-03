#include "Invite.hpp"
#include "../Mode.hpp"

Invite::Invite() {
	this->_is_enabled = false;
}

Invite::~Invite() {}

Invite::Invite(const Invite &copy) : Mode(copy) {
	*this = copy;
}

Invite	&Invite::operator=(const Invite &copy) {
	if (this != &copy) {
		this->_is_enabled = copy._is_enabled;
	}
	return *this;
}

bool	Invite::isEnabled() const {
	return this->_is_enabled;
}

void	Invite::enable() {
	this->setEnable(true);
}

void	Invite::disable() {
	this->setEnable(false);
}

void	Invite::setEnable(bool enable) {
	this->_is_enabled = enable;
}
