# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gedemais <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 12:37:04 by gedemais          #+#    #+#              #
#    Updated: 2019/10/07 12:37:49 by gedemais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COR_NAME=corewar
ASM_NAME=asm

COR_PATH=corewar_prog/
ASM_PATH=asm_prog/

LIB_PATH=libft/
LIB=$(LIB_PATH)libft.a

DEBUG ?= 0

all: $(LIB) $(COR_NAME) $(ASM_NAME)

$(COR_NAME): $(COR_PATH)
ifeq ($(DEBUG), 1)
	@make -C DEBUG=1 $(COR_PATH)
else
	@make -C $(COR_PATH)
endif

$(ASM_NAME): $(ASM_PATH)
ifeq ($(DEBUG), 1)
	@make -C DEBUG=1 $(ASM_PATH)
else
	@make -C $(ASM_PATH)
endif

$(LIB): $(LIB_PATH)
	@make -C $(LIB_PATH)

clean:
	@make -C $(LIB_PATH) clean
	@make -C $(COR_PATH) clean
	@make -C $(ASM_PATH) clean

fclean:
	@make -C $(LIB_PATH) fclean
	@make -C $(COR_PATH) fclean
	@make -C $(ASM_PATH) fclean


