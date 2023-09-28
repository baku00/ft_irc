#ifndef PARSER_HPP
# define PARSER_HPP

# include <main.hpp>

class Parser {
	private:
		static std::string					removeEndOfLine(std::string input);
		static std::string					trim(std::string input);

	public:
		Parser();
		~Parser();
		static std::string					getCommand(std::string input);
		static std::vector<std::string>		getParameters(std::string input);
};

#endif