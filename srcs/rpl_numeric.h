#ifndef RPL_NUMERIC
# define RPL_NUMERIC

// https://datatracker.ietf.org/doc/html/rfc2812#section-5.1
// The server sends Replies 001 to 004 to a user upon
// successful registration.
# define RPL_WELCOME "001",  "Welcome to the Internet Relay Network <nick>!<user>@<host>"
# define RPL_YOURHOST "002",  "Your host is <servername>, running version <ver>"
# define RPL_CREATED "003",  "This server was created <date>"
# define RPL_MYINFO "004",  "<servername> <version> <available user modes> <available channel modes>"

#define RPL_WHOISUSER "311", "<nick> <user> <host> * :<real name>"

# define RPL_NAMREPLY "353", "= <channel> :@<all_nicks>"
# define RPL_ENDOFNAMES "366", "<channel> :End of NAMES list"
# define RPL_TOPIC "332", "<channel> :<topic>"
# define RPL_INVITING "341", "<channel> <nick>"

# define RPL_ADDOPERATOR "381", "Gives 'chanop' to <nick> on <channel>"

#endif