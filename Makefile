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
NAME_BONUS = fractol_bonus
SRC = ./Mandatory/fractol.c ./Mandatory/fractal_functions.c ./Mandatory/fractol_utils.c ./Mandatory/ft_for_mlx.c ./Mandatory/commands.c ./Mandatory/operations.c
SRC_B = ./Bonus/fractol_bonus.c ./Bonus/fractal_functions_bonus.c ./Bonus/fractol_utils_bonus.c ./Bonus/ft_for_mlx_bonus.c ./Bonus/commands_bonus.c ./Bonus/operations_bonus.c
OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)
FLAGS = -Wall -Wextra -Werror -O3
LIBS = -Lminilibx-linux -lmlx -lX11 -lXext -lm
CC = cc

all: $(NAME)

minilibx:
	@$(MAKE) -C minilibx-linux

$(NAME): minilibx $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $(NAME)
	
bonus : minilibx $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_B)
	$(CC) $(OBJ_B) $(LIBS) -o $(NAME_BONUS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(MAKE) -C minilibx-linux clean
	rm -f $(OBJ) $(OBJ_B)

fclean: clean
	$(MAKE) -C minilibx-linux clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re minilibx
