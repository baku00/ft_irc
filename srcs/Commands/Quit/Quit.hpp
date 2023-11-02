#ifndef QUIT_HPP
# define QUIT_HPP

# include <main.hpp>
# include "../ACommand.hpp"
# include "../../Client/Client.hpp"

class Quit : public ACommand {
	public:
		Quit();
		virtual ~Quit();
		virtual void		execute(Client &client, std::vector<std::string> args) const;
};

#endif
