#ifndef WHOIS_HPP
# define WHOIS_HPP

# include <main.hpp>
# include "../ACommand.hpp"
# include "../../Client/Client.hpp"

class Whois : public ACommand {
	public:
		Whois();
		virtual ~Whois();
		virtual void		execute(Client &client, std::vector<std::string> args) const;
};

#endif