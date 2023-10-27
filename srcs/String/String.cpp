#include "String.hpp"

String::String() {}

String::~String() {}

std::string					String::trim(std::string input, std::string chars)
{
	size_t first = input.find_first_not_of(chars);
	size_t last = input.find_last_not_of(chars);

	if (first == std::string::npos || last == std::string::npos)
		return "";

	return input.substr(first, (last - first + 1));
}
