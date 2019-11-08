#ifndef GLOBAL_H
# define GLOBAL_H

# include "asm.h"

# define BLACK "\033[22;30m"
# define BLUE "\033[1;36m"
# define RED "\033[1;31m"
# define L_RED "\033[1;31m"
# define L_GREEN "\033[1;32m"
# define GRA "\033[1m"
# define STOP "\033[0m"

static char				(*g_token_fts[NB_TOKENS_FUNCS])(t_env*, char*, unsigned int*) = {
						[TOK_P_NAME - 1] = &get_tok_p_name,
						[TOK_P_COM - 1] = &get_tok_p_com,
						[TOK_STRING - 1] = &get_tok_string,
						[TOK_REG - 1] = &get_tok_reg,
						[TOK_LABEL - 1] = &get_tok_label,
						[TOK_NUMBER - 1] = &get_tok_number,
						[TOK_LNUMBER - 1] = &get_tok_lnumber,
						[TOK_DLABA - 1] = &get_tok_dlaba,
						[TOK_INDLABA - 1] = &get_tok_indlaba,
						[TOK_OPCODE - 1] = &get_tok_opcode,
						[TOK_SEPARATOR - 1] = &get_tok_separator,
						[TOK_NEWLINE - 1] = &get_tok_newline,
						[TOK_COMMENT - 1] = &get_tok_comment
};

static char				*g_opnames[NB_OPS] = {"add",
											"aff",
											"and",
											"fork",
											"lfork",
											"ld",
											"ldi",
											"lld",
											"lldi",
											"live",
											"or",
											"st",
											"sti",
											"sub",
											"xor",
											"zjmp"};

static char						g_opcodes[NB_OPS] = {4, 16, 6, 12, 15, 2, 10, 13, 14, 1, 7, 3, 11, 5, 8, 9};

static int						g_direct_size[NB_OPS] = {4, 4, 4, 2, 2, 4, 2, 4, 2, 4, 4, 4, 2, 4, 4, 2};


#endif
