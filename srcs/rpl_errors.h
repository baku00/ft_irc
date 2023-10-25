#ifndef RPL_ERRORS
# define RPL_ERRORS

# define ERR_NOSUCHNICK "401", "<nick> :No such nick/channel"
# define ERR_NOSUCHCHANNEL "403", "<channel name> :No such channel"
# define ERR_UNKNOWNCOMMAND "421", "<command> :Unknown command"
# define ERR_NICKNAMEINUSE "433", "<nick> :Nickname is already in use"
# define ERR_NOTONCHANNEL "442", "<channel> :You're not on that channel"
# define ERR_USERONCHANNEL "443", "<user> <channel> :is already on channel"
# define ERR_NEEDMOREPARAMS "461", "<command> :Not enough parameters"
# define ERR_PASSWDMISMATCH "464", ":Password incorrect"
# define ERR_INVITEONLYCHAN "473", "<channel> :Cannot join channel (+i)"
# define ERR_CHANOPRIVSNEEDED "482", "<channel> :You're not channel operator"

#endif