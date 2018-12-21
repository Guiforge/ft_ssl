# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/23 09:03:46 by gpouyat           #+#    #+#              #
#    Updated: 2018/12/21 20:52:34 by gpouyat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = gcc

FLAGS = -Wall -Wextra -Werror

ifeq ($(DEV),yes)
    FLAGS		+= -g
endif

ifeq ($(SAN),yes)
    FLAGS		+= -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif

NAME = ft_ssl

C_NO = \033[0m
C_G = \033[0;32m
C_Y = \033[1;33m
C_B = \033[1;34m
C_C = \033[1;36m
C_R = \033[1;31m

SRC_PATH_SSL = ./srcs/ssl
SRC_PATH_MD5 = ./srcs/md5
# SRC_PATH_MISC = ./srcs/misc
LIB_PATH = ./libft
INC_PATH = ./includes
INC_LIB = ./libft/includes
OBJ_PATH = ./obj
OBJ_PATH_SSL = ./obj/ssl
OBJ_PATH_MD5 = ./obj/md5
# OBJ_PATH_MISC = ./obj/misc

SRC_NAME_SSL = main.c

SRC_NAME_MD5 = main.c

# SRC_NAME_MISC = option.c

OBJ_NAME_SSL = $(SRC_NAME_SSL:.c=.o)
OBJ_NAME_MD5 = $(SRC_NAME_MD5:.c=.o)
# OBJ_NAME_MISC = $(SRC_NAME_MISC:.c=.o)
LIB_NAME = libft.a

SRC_SSL = $(addprefix $(SRC_PATH_SSL)/, $(SRC_NAME_SSL))
SRC_MD5 = $(addprefix $(SRC_PATH_MD5)/, $(SRC_NAME_MD5))
# SRC_MISC = $(addprefix $(SRC_PATH_MISC)/, $(SRC_NAME_MISC))
LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))
# OBJ_SSL = $(addprefix $(OBJ_PATH_SSL)/,$(OBJ_NAME_SSL))
OBJ_MD5 = $(addprefix $(OBJ_PATH_MD5)/,$(OBJ_NAME_MD5))
OBJ_MISC = $(addprefix $(OBJ_PATH_MISC)/,$(OBJ_NAME_MISC))

all: $(NAME_SSL)

$(NAME_SSL): $(LIB) $(OBJ_MISC) $(OBJ_SSL) $(OBJ_MD5)
	$(CC) -o $(NAME_SSL) $(FLAGS) $(OBJ_SSL) $(OBJ_MD5) $(LIB)
	@printf "$(C_G)%-20s\t$(C_Y)Compilation\t$(C_G)[ OK ✔ ]$(C_NO)\n\n" $(NAME_SSL)

$(OBJ_PATH_SSL)/%.o: $(SRC_PATH_SSL)/%.c
	@mkdir -p $(OBJ_PATH) $(OBJ_PATH_SSL)
	$(CC) $(FLAGS) -o $@ -c $< -I $(INC_PATH) -I $(INC_LIB)

$(OBJ_PATH_MD5)/%.o: $(SRC_PATH_MD5)/%.c
	@mkdir -p $(OBJ_PATH) $(OBJ_PATH_MD5)
	$(CC) $(FLAGS) -o $@ -c $< -I $(INC_PATH) -I $(INC_LIB)

#$(OBJ_PATH_MISC)/%.o: $(SRC_PATH_MISC)/%.c
#	@mkdir -p $(OBJ_PATH) $(OBJ_PATH_MISC)
#	$(CC) $(FLAGS) -o $@ -c $< -I $(INC_PATH) -I $(INC_LIB)

$(LIB):
	@make -C $(LIB_PATH) DEV=$(DEV) SAN=$(SAN)

miniclean:
	@rm -rf $(OBJ_SSL)
	@rm -rf $(OBJ_MD5)
	@printf "$(C_B)%-20s\t$(C_Y)Cleaning obj\t$(C_G)[ OK ✔ ]$(C_NO)\n" $(NAME_SSL) $(NAME_MD5)

clean:
	@rm -rf $(OBJ_SSL)
	@rm -rf $(OBJ_MD5)
	@make -C $(LIB_PATH) clean
	@printf "$(C_B)%-20s\t$(C_Y)Cleaning obj\t$(C_G)[ OK ✔ ]$(C_NO)\n" $(NAME_SSL) $(NAME_MD5)

fclean:
	@rm -rf ./obj $(NAME_SSL) $(NAME_MD5)
	@make -C $(LIB_PATH) fclean
	@printf "$(C_B)%-20s\t$(C_Y)Cleaning binary\t$(C_G)[ OK ✔ ]$(C_NO)\n" $(NAME_SSL) $(NAME_MD5)

minire: clean all

re: fclean all
