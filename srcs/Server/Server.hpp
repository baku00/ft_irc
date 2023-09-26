#ifndef SERVER_HPP
# define SERVER_HPP

# include <main.hpp>

class Server
{
	private:
		int			_port;
		std::string	_password;
		int			_serverSocket;
		int			_clientSocket;

		Server();

	public:
		Server(int port, std::string password);
		~Server();
		Server(const Server &copy);
		Server &operator=(const Server &copy);

		void	start();
		void	sendWelcomeMessage(int clientSocket);
};

#endif