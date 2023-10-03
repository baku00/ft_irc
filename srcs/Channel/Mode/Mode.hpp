#ifndef CHANNEL_MODE_HPP
#define CHANNEL_MODE_HPP

#include <iostream>

class Invite;

class Mode {
	private:
		Invite *_invite;

	public:
		Mode();
		~Mode();
		Mode(const Mode &copy);

		Mode &operator=(const Mode &copy);

		Invite &invite();
};

#endif