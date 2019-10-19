# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gedemais <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/23 03:23:53 by gedemais          #+#    #+#              #
#    Updated: 2019/10/19 17:09:18 by moguy            ###   ########.fr        #
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

NAME=corewar
INSPECTION=glaoui

CC=gcc
CFLAGS= -Weverything -Wall -Werror -Wextra

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += -g3 -fsanitize=address
endif

LIB_PATH=../libft/
LIB=$(LIB_PATH)libft.a

INC_PATH=includes/
INC_NAME=	corewar.h\
			op.h\
			define.h

INC=$(addprefix $(INC_PATH), $(INC_NAME))

SRCS_PATH=srcs/
SRCS_NAME=	main.c\
			add_instruction.c\
			aff.c\
			after_space.c\
			after_word.c\
			check.c\
			check_type.c\
			convert_instruction.c\
			conv_table.c\
			cw_loop.c\
			get_name_len.c\
			loader.c\
			load_op.c\
			lst.c\
			merge_args.c\
			op_function.c\
			reverse_bits.c


SRCS_TEST= loader.c\
		   main_test.c\
		   check.c\
		   get_name_len.c\
		   lst.c\
		   aff.c\
		   merge_args.c

SRCS=$(addprefix $(SRCS_PATH), $(SRCS_NAME))
S_TEST=$(addprefix $(SRCS_PATH), $(SRCS_TEST))

OBJS_PATH=objs/
OBJS_NAME=$(SRCS_NAME:.c=.o)

OBJS_PATH_TEST=objstest/
OBJS_TEST=$(SRCS_TEST:.c=.o)

OBJS=$(addprefix $(OBJS_PATH), $(OBJS_NAME))
O_TEST=$(addprefix $(OBJS_PATH_TEST), $(OBJS_TEST))

all: $(LIB) $(NAME) 

inspection: $(LIB) $(INSPECTION)

$(LIB):
	@make -C $(LIB_PATH)

$(INSPECTION) : $(O_TEST)
	@$(CC) $(CFLAGS) -o $(INSPECTION) -I $(INC_PATH) $(O_TEST)  $(LIB)
	@cp $(INSPECTION) ../
	@echo "$(GRE)Done !$(DEF)"

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) -I $(INC_PATH) $(OBJS)  $(LIB)
	@cp $(NAME) ../
	@echo "$(GRE)Done !$(DEF)"

$(OBJS_PATH_TEST)%.o : $(SRCS_PATH)%.c $(INC)
	@echo "Making $(RED)Inspection du travail$(DEF)..."
	@mkdir -p $(OBJS_PATH_TEST)
	@$(CC) $(CFLAGS) -c $(S_TEST) -I $(INC_PATH)
	@mv $(OBJS_TEST) $(OBJS_PATH_TEST)

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c $(INC)
	@echo "Making $(RED)COREWAR virtual machine$(DEF)..."
	@mkdir -p $(OBJS_PATH)
	@$(CC) $(CFLAGS) -c $(SRCS) -I $(INC_PATH)
	@mv $(OBJS_NAME) $(OBJS_PATH)

clean:
	@rm -rf $(OBJS_PATH)
	@rm -rf $(OBJS_PATH_TEST)
	@make -C $(LIB_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(INSPECTION)
	@make -C $(LIB_PATH) fclean


re: fclean all
