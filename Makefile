NAME = irc

SERVER = srcs/Server/Server.cpp

FILES = srcs/main.cpp $(SERVER)

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