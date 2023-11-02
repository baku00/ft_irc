#ifndef TOPIC_HPP
# define TOPIC_HPP

# include <main.hpp>
# include "../ACommand.hpp"
# include "../../Client/Client.hpp"

class Topic : public ACommand {
	private:
		std::string		getChannel(std::vector<std::string> args) const;
		std::string		getTopic(std::vector<std::string> args) const;
		bool			containsTopic(std::vector<std::string> args) const;
		void			setTopic(Client client, Channel *channel, std::vector<std::string> args) const;

	public:
		Topic();
		virtual ~Topic();
		virtual void		execute(Client & client, std::vector<std::string> args) const;
};

#endif
