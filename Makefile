# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpouyat <gpouyatstudent.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/23 09:03:46 by gpouyat           #+#    #+#              #
#    Updated: 2018/12/22 16:16:45 by gpouyat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = gcc

FLAGS = -Wall -Wextra -Werror

ifeq ($(DEBUG),yes)
    FLAGS		+= -D DEBUG
endif

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

#### PATH
SRC_PATH = ./srcs
LIB_PATH = ./libft
INC_PATH = ./includes
OBJ_PATH = ./obj
INC_PATH_LIB = $(LIB_PATH)/$(INC_PATH)

#### SRCS
SRC_NAME += ssl/main.c md5/md5.c md5/padding.c


# vpath  %c $(addprefix $(SRCS_PATH)/,$(SRC_SUBDIR))


HEADERS = ft_ssl.h

OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = libft.a


SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))
HEAD = $(addprefix $(INC_PATH)/, $(HEADERS))

all: $(NAME)

$(NAME): $(LIB) $(OBJ) $(HEAD)
	$(CC) -o $(NAME) $(FLAGS) $(OBJ) $(LIB)
	@printf "$(C_G)\n%-20s\t$(C_Y)Compilation\t$(C_G)[ OK ✔ ]$(C_NO)\n" $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(OBJ_PATH) $(OBJ_PATH)/ssl $(OBJ_PATH)/md5
	$(CC) $(FLAGS) -o $@ -c $< -I $(INC_PATH) -I $(INC_PATH_LIB)

$(LIB):
	make -C $(LIB_PATH)

clean:
	rm -rf $(OBJ)
	make -C $(LIB_PATH) clean
	@printf "$(C_B)%-20s\t$(C_Y)Cleaning obj\t$(C_G)[ OK ✔ ]$(C_NO)\n" $(NAME)

fclean: 
	rm -rf ./obj $(NAME)
	make -C $(LIB_PATH) fclean
	@printf "$(C_B)%-20s\t$(C_Y)Cleaning binary\t$(C_G)[ OK ✔ ]$(C_NO)\n" $(NAME)

re: fclean all
