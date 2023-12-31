#ifndef RPL_ERRORS
# define RPL_ERRORS

# define ERR_NOSUCHNICK "401", "<nick> :No such nick/channel"
# define ERR_NOSUCHCHANNEL "403", "<channel> :No such channel"
# define ERR_UNKNOWNCOMMAND "421", "<command> :Unknown command"
# define ERR_NICKNAMEINUSE "433", "<nick> :Nickname is already in use"
# define ERR_USERNOTINCHANNEL "441", "<nick> <channel> :They aren't on that channel"
# define ERR_NOTONCHANNEL "442", "<channel> :You're not on that channel"
# define ERR_USERONCHANNEL "443", "<user> <channel> :is already on channel"
# define ERR_NEEDMOREPARAMS "461", "<command> :Not enough parameters"
# define ERR_ALREADYREGISTRED "462", ":You may not reregister"
# define ERR_PASSWDMISMATCH "464", ":Password incorrect"
# define ERR_INVITEONLYCHAN "473", "<channel> :Cannot join channel (+i)"
# define ERR_CHANOPRIVSNEEDED "482", "<channel> :You're not channel operator"
# define ERR_RESTRICTED "484", ":Your connection is restricted!"
# define RPL_NOTOPIC "331", "<channel> :No topic is set"
# define RPL_TOPIC "332", "<channel> :<topic>"
# define ERR_UMODEUNKNOWNFLAG "501", ":Unknown MODE flag"
# define ERR_INVALIDKEY "475", "<channel> :Cannot join channel (+k)"
# define ERR_CHANNELISFULL "471", "<channel> :Cannot join channel (+l)"
# define ERR_UNKNOWNMODE "472", "<char> :is unknown mode char to me for <channel>"
# define ERR_CHANOPRIVSNEEDED "482", "<channel> :You're not channel operator"

#endif
