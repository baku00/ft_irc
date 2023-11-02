#ifndef ME_HPP
# define ME_HPP

# include <main.hpp>
# include "../ACommand.hpp"
# include "../../Client/Client.hpp"

class Me : public ACommand {
	private:
		std::string		getUsername(std::vector<std::string> args) const;

	public:
		Me();
		virtual ~Me();
		virtual void		execute(Client &client, std::vector<std::string> args) const;
};

#endif
