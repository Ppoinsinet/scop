SRC = src/main.cpp src/class/ObjParser.cpp src/utils.cpp src/class/Vertice.cpp src/class/Face.cpp src/class/Shader.cpp

OBJS = $(SRC:.cpp=.o)

NAME = scop

CC = clang++

FLAGS = -Wall -Wextra -Werror -g

LIBS = -lglfw -lGL

INCLUDE = include/

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(LIBS) $(OBJS)

.cpp.o:
	$(CC) $(FLAGS) $< -c -o $(<:.cpp=.o) -I$(INCLUDE)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re # Not representing files