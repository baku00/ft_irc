NAME = ircserv

SERVER = srcs/Server/Server.cpp
INSTANCE = srcs/Server/Instance/ServerInstance.cpp
CLIENT = srcs/Client/Client.cpp
PARSER = srcs/Parser/Parser.cpp
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
MESSAGE = srcs/Utils/Message/Message.cpp

FILES = srcs/main.cpp \
		$(SERVER) $(CLIENT) $(PARSER) \
		$(AUTH)	$(A_COMMAND) $(INSTANCE) \
		$(PASS) $(PRIV_MSG) $(NICK) \
		$(USER) $(ME) $(QUIT) \
		$(JOIN) \
		$(MESSAGE) $(PING)

OBJS = $(FILES:.cpp=.o)

FLAGS = -Wall -Wextra -Werror -std=c++98 -I./srcs

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