#ifndef NICK_HPP
# define NICK_HPP

# include <main.hpp>
# include "../ACommand.hpp"
# include "../../Client/Client.hpp"

class Nick : public ACommand {
	private:
		std::string		getNickname(std::vector<std::string> args) const;

	public:
		Nick();
		virtual ~Nick();
		virtual void		execute(Client &client, std::vector<std::string> args) const;

		static bool			isValidNickname(std::string nickname);
};

#endif