#ifndef PRIV_MSG_HPP
# define PRIV_MSG_HPP

# include <main.hpp>
# include "../ACommand.hpp"
# include "../../Client/Client.hpp"
# include "../Nick/Nick.hpp"

class PrivMsg : public ACommand {
	private:
		std::string		getUsername(std::vector<std::string> args) const;
		std::string		getMessage(std::vector<std::string> args) const;
		void			sendMessage(Client client, std::string username, std::string message) const;
		bool			isToChannel(std::string channel_name) const;

	public:
		PrivMsg();
		virtual ~PrivMsg();
		virtual void		execute(Client client, std::vector<std::string> args) const;
};

#endif
