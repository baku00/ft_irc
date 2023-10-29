#ifndef MODE_HPP
# define MODE_HPP

# include <main.hpp>
# include <Commands/ACommand.hpp>
# include <Client/Client.hpp>
# include <rpl_errors.h>
# include <rpl_numeric.h>

class Mode : public ACommand {
	private:
		std::string		getMode(std::vector<std::string> args) const;
		std::string		getChannel(std::vector<std::string> args) const;
		std::string		getValue(std::vector<std::string> args) const;

	public:
		Mode();
		virtual ~Mode();
		virtual void		execute(Client &client, std::vector<std::string> args) const;
};

#endif