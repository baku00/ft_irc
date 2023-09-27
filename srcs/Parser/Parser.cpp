#include "Parser.hpp"

std::string					Parser::trim(std::string input)
{
	size_t first = input.find_first_not_of(" \t\n\r");
	if (first == std::string::npos) {
		// La chaîne est vide ou ne contient que des espaces
		return "";
	}
	
	size_t last = input.find_last_not_of(" \t\n\r");
	return input.substr(first, (last - first + 1));
}

std::string					Parser::getCommand(std::string input) {
	std::string	command;

	input = Parser::trim(input);
	command = input.substr(0, input.find(" "));
	return command;
}

std::vector<std::string>	Parser::getParameters(std::string input) {
	std::vector<std::string>	parameters;
	std::string					parameter;
	std::string					command;
	//size_t						start;

	input = Parser::trim(input);
	command = Parser::getCommand(input);
	input = input.substr(input.find(" ") + 1);
	parameters.push_back(command);
	input = input.substr(command.length());

	while (input.find(" ") != std::string::npos) {
		//start = input.find_first_not_of(" ");
		parameter = input.substr(command.length(), input.find(" "));
		parameters.push_back(parameter);
		input = input.substr(input.find(" ") + 1);
	}
	if (input.length() > 0)
		parameters.push_back(input);
	return parameters;
}
