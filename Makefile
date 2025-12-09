# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 19:22:13 by sdell-er          #+#    #+#              #
#    Updated: 2024/08/08 11:31:09 by sdell-er         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
SRC = ./srcs/fractol_bonus.c ./srcs/fractal_functions_bonus.c ./srcs/fractol_utils_bonus.c ./srcs/ft_for_mlx_bonus.c ./srcs/commands_bonus.c ./srcs/operations_bonus.c
OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror -O3
LIBS = -Lminilibx-linux -lmlx -lX11 -lXext -lm
CC = cc

all: $(NAME)

minilibx:
	@$(MAKE) -C minilibx-linux > /dev/null 2>&1

$(NAME): minilibx $(OBJ)
	@$(CC) $(OBJ) $(LIBS) -o $(NAME) > /dev/null
	@echo "\e[0;93m[$(NAME)] compiled!\e[0m"

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(MAKE) -C minilibx-linux clean > /dev/null
	@rm -f $(OBJ)
	@echo "\e[0;91mcleaned!\e[0m"

fclean: clean
	@$(MAKE) -C minilibx-linux clean > /dev/null
	@rm -f $(NAME)
	@echo "\e[0;91m[$(NAME)] deleted!\e[0m"

re: fclean all

.PHONY: all clean fclean re minilibx
