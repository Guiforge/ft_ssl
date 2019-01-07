# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpouyat <gpouyat@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/05 12:29:27 by gpouyat           #+#    #+#              #
#    Updated: 2019/01/07 18:52:21 by gpouyat          ###   ########.fr        #
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

SRC_SUBDIR 		= ssl
SRCS			+= main.c

SRC_SUBDIR 		+= md5
SRCS			+= final.c get.c init.c md5.c operations.c print_sum.c update.c

SRC_SUBDIR 		+= sha-256
SRCS			+= final.c get.c init.c sha256.c operations.c print_sum.c update.c

SRC_SUBDIR		+= misc
SRCS			+= buffer512.c

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

vpath  %c $(addprefix $(SRCS_DIR)/, $(SRC_SUBDIR))

#Objects
OBJS_DIR		= objs
 OBJS			= $(SRCS:%.c=$(OBJS_DIR)/%.o)

BUILD_DIR		= $(OBJS_DIR)

#Utils
RM			= rm -rf
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

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
	$(eval PERCENT=$(shell echo $$((($(COUNT) * 100 )/$(TOTAL)))))
	@printf "$(C_B)%-8s $(C_NO)" "[$(PERCENT)%]"

$(BUILD_DIR):
	@$(MKDIR) $@

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
