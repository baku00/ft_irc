#include "ACommand.hpp"

ACommand::ACommand() {
}

ACommand::~ACommand() {
}

bool	ACommand::isValidArgsNumber(int args) const
{
	if (_minArgsRequired == -1 && _maxArgsRequired == -1)
		return true;
	if (_minArgsRequired == -1 && args <= _maxArgsRequired)
		return true;
	if (_maxArgsRequired == -1 && args >= _minArgsRequired)
		return true;
	if (_minArgsRequired == _maxArgsRequired && args == _minArgsRequired)
		return true;
	if (args >= _minArgsRequired && args <= _maxArgsRequired)
		return true;
	return false;
}
