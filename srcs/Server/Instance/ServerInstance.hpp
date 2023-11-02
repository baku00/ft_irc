#ifndef SERVER_INSTANCE_HPP
# define SERVER_INSTANCE_HPP

# include <main.hpp>
# include "../Server.hpp"

class Server;

class ServerInstance
{
	private:
		static Server	*_server;

		ServerInstance();
		~ServerInstance();
		ServerInstance(const ServerInstance &copy);
		ServerInstance &operator=(const ServerInstance &copy);

	public:
		static Server	*getInstance();
		static void		destroyInstance();
		static Server	*createInstance(int port, std::string password);
};

#endif
