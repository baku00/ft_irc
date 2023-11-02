#ifndef MODE_HPP
# define MODE_HPP

# include <main.hpp>
# include "../ACommand.hpp"
# include "../../Client/Client.hpp"

class Mode : public ACommand {
	private:
		std::string		getMode(std::vector<std::string> args) const;
		std::string		getChannel(std::vector<std::string> args) const;
		std::string		getValue(std::vector<std::string> args) const;
		bool			isForSet(std::string mode) const;
		bool			isValidMode(std::string mode) const;

	public:
		Mode();
		virtual ~Mode();

		virtual void		execute(Client &client, std::vector<std::string> args) const;
};

#endif
