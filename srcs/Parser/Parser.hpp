#ifndef PARSER_HPP
# define PARSER_HPP

# include <main.hpp>
# include "../Commands/ACommand.hpp"
# include "../Client/Client.hpp"

class ACommand;
class Client;

class Parser {
	private:
		std::map<std::string, ACommand *>	_commands;

		void								_deleteCommands();

	public:
		Parser();
		~Parser();
		static std::string					getChannel(std::string input);
		static std::string					getCommand(std::string input);
		static std::vector<std::string>		getParameters(std::string input);
		void								execute(Client &client, std::string command, std::vector<std::string> args);
};

#endif
