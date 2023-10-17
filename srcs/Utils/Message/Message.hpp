#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <iostream>

class Message {
	private:
		int			_sender;
		std::string	_fullname;
		std::string	_content;
		Message();

	public:
		Message(int sender, std::string fullname, std::string content);
		~Message();
		Message(const Message &copy);

		Message &operator=(const Message &copy);

		int			getSender() const;
		std::string	getContent() const;
		std::string	getFullname() const;

		void		setSender(int sender);
		void		setFullname(std::string fullname);
		void		setContent(std::string content);
};

#endif