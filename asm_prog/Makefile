# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gedemais <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/23 03:23:53 by gedemais          #+#    #+#              #
#    Updated: 2019/10/10 14:03:02 by demaisonc        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEF = \033[0m
GRA = \033[1m
SOU = \033[4m
BLI = \033[5m
BLA = \033[30m
RED = \033[31m
GRE = \033[32m
YEL = \033[33m
BLU = \033[34m
PUR = \033[35m
CYA = \033[36m
WHI = \033[37m
ORG = \033[1;31m

NAME=asm

CC=gcc
CFLAGS= -Weverything -Wall -Werror -Wextra

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += -g3 -fsanitize=address
endif

LIB_PATH=../libft/
LIB=$(LIB_PATH)libft.a

INC_PATH=includes/
INC_NAME=	asm.h\
			op.h
INC=$(addprefix $(INC_PATH), $(INC_NAME))

SRCS_PATH=srcs/
SRCS_NAME=	main.c\
			loader.c\
			tokenizer.c\
			token_lst.c\
			free.c
SRCS=$(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH=objs/
OBJS_NAME=$(SRCS_NAME:.c=.o)

OBJS=$(addprefix $(OBJS_PATH), $(OBJS_NAME))

all: $(LIB) $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) -I $(INC_PATH) $(OBJS)  $(LIB)
	@echo "$(GRE)Done !$(DEF)"

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c $(INC)
	@echo "Making $(RED)ASM Compiler$(DEF)..."
	@mkdir -p $(OBJS_PATH)
	@$(CC) $(CFLAGS) -c $(SRCS) -I $(INC_PATH)
	@mv $(OBJS_NAME) $(OBJS_PATH)

clean:
	@rm -rf $(OBJS_PATH)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
