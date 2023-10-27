#include "Parser.hpp"
#include "../Commands/Pass/Pass.hpp"
#include "../Commands/PrivMsg/PrivMsg.hpp"
#include "../Commands/Nick/Nick.hpp"
#include "../Commands/User/User.hpp"
#include "../Commands/Me/Me.hpp"
#include "../Commands/Quit/Quit.hpp"
#include "../Commands/Join/Join.hpp"
#include "../Commands/Ping/Ping.hpp"
#include "../Commands/Kick/Kick.hpp"
#include "../Commands/Invite/Invite.hpp"
#include "../Commands/Topic/Topic.hpp"
#include "../String/String.hpp"

Parser::Parser() {
	this->_commands.insert(std::pair<std::string, ACommand *>("PASS", new Pass()));
	this->_commands.insert(std::pair<std::string, ACommand *>("PRIVMSG", new PrivMsg()));
	this->_commands.insert(std::pair<std::string, ACommand *>("NICK", new Nick()));
	this->_commands.insert(std::pair<std::string, ACommand *>("USER", new User()));
	this->_commands.insert(std::pair<std::string, ACommand *>("userhost", new User()));
	this->_commands.insert(std::pair<std::string, ACommand *>("ME", new Me()));
	this->_commands.insert(std::pair<std::string, ACommand *>("QUIT", new Quit()));
	this->_commands.insert(std::pair<std::string, ACommand *>("JOIN", new Join()));
	this->_commands.insert(std::pair<std::string, ACommand *>("PING", new Ping()));
	this->_commands.insert(std::pair<std::string, ACommand *>("KICK", new Kick()));
	this->_commands.insert(std::pair<std::string, ACommand *>("INVITE", new Invite()));
	this->_commands.insert(std::pair<std::string, ACommand *>("TOPIC", new Topic()));
}

Parser::~Parser() {}

std::string					Parser::getCommand(std::string input) {
	size_t space_pos = input.find(" ");
	if (space_pos == std::string::npos)
		return String::trim(input, " \t\n\r");
	return String::trim(input.substr(0, space_pos), " \t\n\r");
}

std::string					Parser::getChannel(std::string input) {
	size_t space_pos = input.find(" ");
	if (space_pos == std::string::npos)
		return String::trim(input, " \t\n\r");
	return String::trim(input.substr(0, space_pos), " \t\n\r");
}

std::vector<std::string>	Parser::getParameters(std::string input) {
	std::vector<std::string>	args;
	size_t						space_pos;
	size_t						double_dot;
	std::string					last_argument;

	double_dot = input.find(":");
	if (double_dot != std::string::npos)
	{
		last_argument = input.substr(double_dot + 1, input.length() - double_dot - 1);
		input = input.substr(0, double_dot);
	}

	while (input.length())
	{
		if ((space_pos = input.find(" ")) == std::string::npos)
		{
			args.push_back(String::trim(input, " \t\n\r"));
			break ;
		}
		else
		{
			std::string arg = input.substr(0, space_pos);
			if (arg.length())
				args.push_back(String::trim(arg, " \t\n\r"));
		}
		input = input.substr(space_pos + 1, input.length() - space_pos - 1);
	}
	if (last_argument.length())
		args.push_back(last_argument);
	return args;
}

void	Parser::execute(Client client, std::string command, std::vector<std::string> args) {
	std::map<std::string, ACommand *>::iterator it = this->_commands.find(command);
	if (it != this->_commands.end())
		it->second->execute(client, args);
	else
	{
		std::cerr << "Command not found: " << command << std::endl;
		client.reply(ERR_UNKNOWNCOMMAND, command.c_str());
	}
}
