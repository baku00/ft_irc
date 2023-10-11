#ifndef PING_HPP
# define PING_HPP

# include <main.hpp>
# include "../ACommand.hpp"
# include "../../Client/Client.hpp"

class Ping : public ACommand {
	public:
		Ping();
		virtual ~Ping();
		virtual void		execute(Client client, std::vector<std::string> args) const;
};

#endif