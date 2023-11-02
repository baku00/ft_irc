#ifndef STRING_HPP
# define STRING_HPP

# include <iostream>

class String {
	private:
		String();
		~String();

	public:
		static std::string	trim(std::string input, std::string chars);
};

#endif
