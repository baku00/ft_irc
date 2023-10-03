#ifndef CHANNEL_MODE_INVITE_HPP
#define CHANNEL_MODE_INVITE_HPP

#include "../Mode.hpp"

class Mode;

class Invite : public Mode {
	private:
		bool _is_enabled;
		void setEnable(bool enable);

	public:
		Invite();
		~Invite();
		Invite(const Invite &copy);

		Invite &operator=(const Invite &copy);

		bool isEnabled() const;
		void enable();
		void disable();
};

#endif