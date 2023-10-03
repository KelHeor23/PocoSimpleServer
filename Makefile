NAME = server
SRCS = 	main.cpp server.cpp
OBJECTS = $(SRCS:.cpp=.o)
LIBS += -lPocoNet -lPocoFoundation
FLAGS=	-Wall -Wextra -Werror -c
CC = g++

all: clean $(NAME)

$(NAME): main.o server.o
	@$(CC) $(OBJECTS) $(LIBS) -o $(NAME)	

main.o:
	@$(CC) $(FLAGS) main.cpp

server.o:
	@$(CC) $(FLAGS) server.cpp

%.o: %.c
	@$(CC) $< -o $@

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all