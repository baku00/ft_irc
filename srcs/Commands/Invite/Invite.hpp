#ifndef INVITE_HPP
# define INVITE_HPP

# include <main.hpp>
# include <Commands/ACommand.hpp>
# include <Client/Client.hpp>
# include <rpl_errors.h>
# include <rpl_numeric.h>

class Invite : public ACommand {
	private:
		std::string		getNickname(std::vector<std::string> args) const;
		std::string		getChannel(std::vector<std::string> args) const;

	public:
		Invite();
		virtual ~Invite();
		virtual void		execute(Client &client, std::vector<std::string> args) const;
};

#endif