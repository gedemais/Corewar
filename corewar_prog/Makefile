# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gedemais <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/23 03:23:53 by gedemais          #+#    #+#              #
#    Updated: 2019/11/03 02:46:28 by moguy            ###   ########.fr        #
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

CC=gcc
CFLAGS= -Wall -Werror -Wextra

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += -g3 -fsanitize=address
endif

LIB_PATH=../libft/
LIB=$(LIB_PATH)libft.a

INC_PATH=includes/
INC_NAME=corewar.h\
			op.h\
			libft.h\
			define.h

INC=$(addprefix $(INC_PATH), $(INC_NAME))

SRCS_PATH=srcs/
SRCS_NAME=	after_space.c\
		after_word.c\
		check_lives.c\
		convert_instruction.c\
		conv_table.c\
		create_launch.c\
		cw_loop.c\
		get_data.c\
		get_id.c\
		get_name_len.c\
		is_valid.c\
		is_valid2.c\
		load_args.c\
		loader.c\
		lst.c\
		main.c\
		merge_args.c\
		op_functions.c\
		opt.c\
		opt_utils.c\
		aff.c\
		reverse_bits.c

SRCS=$(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH=objs/
OBJS_NAME=$(SRCS_NAME:.c=.o)

OBJS=$(addprefix $(OBJS_PATH), $(OBJS_NAME))

all: $(LIB) $(NAME) 

$(LIB):
	@make -C $(LIB_PATH)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) -I $(INC_PATH) $(OBJS) $(LIB)
	@cp $(NAME) ../
	@echo "$(GRE)Done !$(DEF)"

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c $(INC)
	@echo "Making $(RED)COREWAR virtual machine$(DEF)..."
	@mkdir -p $(OBJS_PATH)
	@$(CC) $(CFLAGS) -c $(SRCS) -I $(INC_PATH)
	@mv $(OBJS_NAME) $(OBJS_PATH)

clean:
	@rm -rf $(OBJS_PATH)
	@make -C $(LIB_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIB_PATH) fclean

re: fclean all
