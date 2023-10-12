#ifndef JOIN_HPP
# define JOIN_HPP

# include <main.hpp>
# include "../ACommand.hpp"
# include "../../Client/Client.hpp"

class Join : public ACommand {
	private:
		std::string		getName(std::vector<std::string> args) const;

	public:
		Join();
		virtual ~Join();
		virtual void		execute(Client client, std::vector<std::string> args) const;
};

#endif