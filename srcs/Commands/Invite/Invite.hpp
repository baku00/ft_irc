#ifndef INVITE_HPP
# define INVITE_HPP

# include <main.hpp>
# include <Commands/ACommand.hpp>
# include <Client/Client.hpp>

class Invite : public ACommand {
	private:
		std::string		getName(std::vector<std::string> args) const;

	public:
		Invite();
		virtual ~Invite();
		virtual void		execute(Client client, std::vector<std::string> args) const;
};

#endif