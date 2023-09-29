#ifndef MSG_HPP
# define MSG_HPP

# include <main.hpp>
# include "../ACommand.hpp"
# include "../../Client/Client.hpp"

class Msg : public ACommand {
	private:
		std::string		getUsername(std::vector<std::string> args) const;
		std::string		getMessage(std::vector<std::string> args) const;
		void			sendMessage(Client client, std::string username, std::string message) const;

	public:
		Msg();
		virtual ~Msg();
		virtual void		execute(Client client, std::vector<std::string> args) const;
};

#endif
