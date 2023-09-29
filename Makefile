NAME = irc

SERVER = srcs/Server/Server.cpp
INSTANCE = srcs/Server/Instance/ServerInstance.cpp
CLIENT = srcs/Client/Client.cpp
PARSER = srcs/Parser/Parser.cpp
AUTH = srcs/Auth/Auth.cpp
A_COMMAND = srcs/Commands/ACommand.cpp
PASS = srcs/Commands/Pass/Pass.cpp

FILES = srcs/main.cpp $(SERVER) $(CLIENT) $(PARSER) $(AUTH)	$(A_COMMAND) $(INSTANCE) $(PASS)

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