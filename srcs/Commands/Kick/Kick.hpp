#ifndef KICK_HPP
# define KICK_HPP

# include <main.hpp>
# include "../ACommand.hpp"
# include "../../Client/Client.hpp"

class Kick : public ACommand {
	private:
		std::string		getChannel(std::vector<std::string> args) const;
		std::string		getNickname(std::vector<std::string> args) const;
		std::string		getReason(std::vector<std::string> args) const;

	public:
		Kick();
		virtual ~Kick();
		virtual void		execute(Client &client, std::vector<std::string> args) const;
};

#endif
