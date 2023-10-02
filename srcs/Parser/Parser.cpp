#include "Parser.hpp"
#include "../Commands/Pass/Pass.hpp"
#include "../Commands/Msg/Msg.hpp"
#include "../Commands/Nick/Nick.hpp"
#include "../Commands/User/User.hpp"
#include "../Commands/Me/Me.hpp"

Parser::Parser() {
	this->_commands.insert(std::pair<std::string, ACommand *>("PASS", new Pass()));
	this->_commands.insert(std::pair<std::string, ACommand *>("MSG", new Msg()));
	this->_commands.insert(std::pair<std::string, ACommand *>("NICK", new Nick()));
	this->_commands.insert(std::pair<std::string, ACommand *>("USER", new User()));
	this->_commands.insert(std::pair<std::string, ACommand *>("ME", new Me()));
}

Parser::~Parser() {}

std::string					Parser::trim(std::string input)
{
	size_t first = input.find_first_not_of(" \t\n\r");
	size_t last = input.find_last_not_of(" \t\n\r");

	if (first == std::string::npos || last == std::string::npos)
		return "";

	return input.substr(first, (last - first + 1));
}

std::string					Parser::getCommand(std::string input) {
	size_t space_pos = input.find(" ");
	if (space_pos == std::string::npos)
		return Parser::trim(input);
	return Parser::trim(input.substr(0, space_pos));
}

std::vector<std::string>	Parser::getParameters(std::string input) {
	std::vector<std::string>	args;
	size_t						space_pos;

	while (input.length())
	{
		if ((space_pos = input.find(" ")) == std::string::npos)
		{
			args.push_back(Parser::trim(input));
			break ;
		}
		else
		{
			std::string arg = input.substr(0, space_pos);
			if (arg.length())
				args.push_back(Parser::trim(arg));
		}
		input = input.substr(space_pos + 1, input.length() - space_pos - 1);
	}
	return args;
}

void						Parser::execute(Client client, std::string command, std::vector<std::string> args) {
	std::map<std::string, ACommand *>::iterator it = this->_commands.find(command);
	if (it != this->_commands.end())
		it->second->execute(client, args);
	else
	{
		std::cerr << "Command not found" << std::endl;
		Client::sendMessage(client.getFd(), "421 '" + command + "' :Unknown command");
	}
}
