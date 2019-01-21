# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/05 12:29:27 by gpouyat           #+#    #+#              #
#    Updated: 2019/01/21 16:34:46 by gpouyat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# .NOTPARALLEL:

.PHONY: all clean fclean re

C_NO = \033[0m
C_G = \033[0;32m
C_Y = \033[1;33m
C_B = \033[1;34m
C_C = \033[1;36m
C_R = \033[1;31m

SRCS			+= /ssl/main.c

SRCS			+= /md5/final.c /md5/init.c /md5/md5.c /md5/operations.c /md5/update.c

SRCS			+= /sha-256/final.c /sha-256/init.c /sha-256/sha256.c /sha-256/operations.c /sha-256/update.c \
							/sha-256/globals_functions_sha.c /sha-256/globals_functions_sha2.c

SRCS			+= /sha-512/final.c /sha-512/init.c /sha-512/sha512.c /sha-512/operations.c /sha-512/update.c \
							/sha-512/globals_functions_sha.c /sha-512/globals_functions_sha2.c

SRCS			+= /sha-384/init.c /sha-384/sha384.c

SRCS			+= /sha-224/init.c /sha-224/sha224.c

SRCS			+= /misc/buffer512.c /misc/buffer1024.c /misc/digst_print.c /misc/digst_get.c /misc/digst_main.c /misc/digst_parse.c

SRC_SUBDIR = ssl misc md5 sha-256 sha-512 sha-384 sha-224

###############################################################################

#  Compiler

NAME 			= ft_ssl
CC			= cc
CFLAGS			= -Wall -Wextra -Werror

ifeq ($(DEBUG), yes)
	CFLAGS		+= -D DEBUG
endif

ifeq ($(DEV),yes)
    CFLAGS		+= -g
endif

ifeq ($(SAN),yes)
    CFLAGS		+= -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif

#The Directories, Source, Includes, Objects and Libraries
INC			= -I includes
SRCS_DIR		= srcs

#Objects
# OBJS = $(addprefix $(OBJS_DIR)/,$(OBJ_NAME))
# OBJS_DIR		= objs
# OBJ = $(SRCS_NAME:.c=.o)# $(SRCS:%.c=$(OBJS_DIR)/%.o)

OBJ_NAME = $(SRCS:.c=.o)
OBJS_DIR	= objs
OBJS = $(addprefix $(OBJS_DIR),$(OBJ_NAME))
OBJS_DIRS = $(addprefix $(OBJS_DIR)/,$(SRC_SUBDIR))


BUILD_DIR		= $(OBJS_DIRS)

#Utils
RM				= rm -rf
MKDIR			= mkdir -p

#LIB
LIB_PATH		= libft
LIB_NAME		= libft.a
LIB				= $(LIB_PATH)/$(LIB_NAME)

COUNT = 0
TOTAL = 0
PERCENT = 0
$(eval TOTAL=$(shell echo $$(printf "%s" "$(SRCS)" | wc -w)))
###############################################################################


all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIB)
	@echo
	@echo "[\033[35m---------------------------------\033[0m]"
	@echo "[\033[36m------- Compilation Done! -------\033[0m]"
	@echo "[\033[35m---------------------------------\033[0m]"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(MKDIR) $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
	$(eval PERCENT=$(shell echo $$((($(COUNT) * 100 )/$(TOTAL)))))
	@printf "$(C_B)%-8s $(C_NO)" "[$(PERCENT)%]"


$(LIB):
	make DEBUG=$(DEBUG) DEV=$(DEV) SAN=$(SAN) -C $(LIB_PATH)

clean:
	@echo "\033[35m$(NAME)  :\033[0m [\033[31mSuppression des .o\033[0m]"
	$(RM) $(OBJS_DIR)
	make clean -C $(LIB_PATH)

fclean: clean
	@echo "\033[35m$(NAME)  :\033[0m [\033[31mSuppression de $(NAME)\033[0m]"
	$(RM) $(NAME)
	make fclean -C $(LIB_PATH)

re: fclean all
