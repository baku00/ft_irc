#include "Mode.hpp"

#include "Invite/Invite.hpp"

Mode::Mode()
{
	this->_invite = new Invite();
}

Mode::Mode(const Mode &copy) {
	*this = copy;
}

Mode::~Mode() {
	delete this->_invite;
}

Mode	&Mode::operator=(const Mode &copy) {
	if (this != &copy) {
	}
	return *this;
}

Invite	&Mode::invite() {
	return *this->_invite;
}