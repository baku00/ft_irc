NAME = ircserv

SERVER = srcs/Server/Server.cpp
INSTANCE = srcs/Server/Instance/ServerInstance.cpp
CLIENT = srcs/Client/Client.cpp
PARSER = srcs/Parser/Parser.cpp
AUTH = srcs/Auth/Auth.cpp
A_COMMAND = srcs/Commands/ACommand.cpp
PASS = srcs/Commands/Pass/Pass.cpp
MSG = srcs/Commands/Msg/Msg.cpp
NICK = srcs/Commands/Nick/Nick.cpp
USER = srcs/Commands/User/User.cpp
ME = srcs/Commands/Me/Me.cpp
QUIT = srcs/Commands/Quit/Quit.cpp
CHANNEL = srcs/Channel/Channel.cpp
MODE = srcs/Channel/Mode/Mode.cpp
INVITE = srcs/Channel/Mode/Invite/Invite.cpp
MESSAGE = srcs/Utils/Message/Message.cpp

FILES = srcs/main.cpp \
		$(SERVER) $(CLIENT) $(PARSER) \
		$(AUTH)	$(A_COMMAND) $(INSTANCE) \
		$(PASS) $(MSG) $(NICK) \
		$(USER) $(ME) $(QUIT) \
		$(CHANNEL) $(MODE) $(INVITE) \
		$(MESSAGE)

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