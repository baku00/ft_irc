NAME = ircserv

SERVER = srcs/Server/Server.cpp
INSTANCE = srcs/Server/Instance/ServerInstance.cpp
CLIENT = srcs/Client/Client.cpp
PARSER = srcs/Parser/Parser.cpp
STRING = srcs/String/String.cpp
AUTH = srcs/Auth/Auth.cpp
A_COMMAND = srcs/Commands/ACommand.cpp
PASS = srcs/Commands/Pass/Pass.cpp
PRIV_MSG = srcs/Commands/PrivMsg/PrivMsg.cpp
NICK = srcs/Commands/Nick/Nick.cpp
USER = srcs/Commands/User/User.cpp
ME = srcs/Commands/Me/Me.cpp
QUIT = srcs/Commands/Quit/Quit.cpp
JOIN = srcs/Commands/Join/Join.cpp
PING = srcs/Commands/Ping/Ping.cpp
KICK = srcs/Commands/Kick/Kick.cpp
INVITE = srcs/Commands/Invite/Invite.cpp
TOPIC = srcs/Commands/Topic/Topic.cpp
MODE = srcs/Commands/Mode/Mode.cpp
CHANNEL = srcs/Channel/Channel.cpp
MESSAGE = srcs/Utils/Message/Message.cpp
TESTS = tests/test_mode.cpp

FILES = srcs/main.cpp $(TESTS) $(TOPIC) \
		$(SERVER) $(CLIENT) $(PARSER) \
		$(AUTH)	$(A_COMMAND) $(INSTANCE) \
		$(PASS) $(PRIV_MSG) $(NICK) \
		$(USER) $(ME) $(QUIT) \
		$(JOIN) $(CHANNEL) $(KICK) \
		$(MESSAGE) $(PING) $(INVITE) \
		$(STRING) $(MODE)

OBJS = $(FILES:.cpp=.o)

FLAGS = -Wall -Wextra -Werror -std=c++98 -I./srcs -I./tests

CC = c++

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re