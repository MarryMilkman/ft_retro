# Name of the program
NAME	:= ft_retro

# Directories
OBJ_DIR	:= ./obj/
SRC_DIR	:= ./src/
INC_DIR := ./inc/

# Source and object files
SRC		:= main.cpp Ship.cpp Game.cpp Coord.cpp Meh.cpp Elem.cpp
OBJ		:= $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

# Header files
INC	:= Ship.hpp Game.hpp Coord.hpp Meh.hpp Elem.hpp

# Compiler and flags
CC		:= clang++
FLAGS	:= -Wall -Wextra -Werror

# Compile and link the program
all: obj_dir $(NAME)

# Link object files into the executable
$(NAME): $(OBJ)
	$(CC) -lncurses $(FLAGS) $(OBJ) -o $(NAME) -I$(INC_DIR)

# Compile object files from source files
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) $(FLAGS) -o $@ -c $< -I$(INC_DIR)

# Create a directory for object files
obj_dir:
	@mkdir -p $(OBJ_DIR)

# Delete object files
clean:
	rm -rf $(OBJ_DIR)

# Delete all files created with the Makefile
fclean: clean
	rm -f $(NAME)

# Re-make all files
re: fclean all

# GNU will run even if files have names as instructions
.PHONY: all clean fclean re
