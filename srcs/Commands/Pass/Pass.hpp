#ifndef PASS_HPP
# define PASS_HPP

# include <main.hpp>
# include "../ACommand.hpp"
# include "../../Client/Client.hpp"

class Pass : public ACommand {
	public:
		Pass();
		virtual ~Pass();
		virtual void		execute(Client client, std::vector<std::string> args) const;
};

#endif
