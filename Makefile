# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 19:22:13 by sdell-er          #+#    #+#              #
#    Updated: 2023/12/07 20:17:05 by sdell-er         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
SRC = fractol.c fractal_functions.c fractol_utils.c ft_for_mlx.c commands.c operations.c
OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror -O3
LIBS = -Lminilibx-linux -lmlx -lX11 -lXext -lm
CC = cc

all: minilibx $(NAME)

minilibx:
	@$(MAKE) -C minilibx-linux

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(MAKE) -C minilibx-linux clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C minilibx-linux clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re minilibx
