/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:48:51 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/10 15:00:24 by demaisonc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../../libft/libft.h"
# include <op.h>
# include <error.h>

# include <stdbool.h>
# include <stdio.h>

# define BLACK "\033[22;30m"
# define BLUE "\033[22;34m"
# define RED "\033[22;31m"
# define L_RED "\033[01;31m"
# define L_GREEN "\033[01;32m"
# define GRA "\033[1m"
# define STOP "\033[0m"

# define USAGE "usage: ./asm [champion.s]"
# define FILE_ERR_MSG "Invalid file or file name :"

# define BUFF_READ 65536

# define NB_OPS 16
# define NB_TOKENS_FUNCS 8
# define FCHAR stream[0]

# define DEBUG_MODE true

typedef enum			e_token_type
{
	TOK_NONE,
	TOK_P_NAME,
	TOK_P_COM,
	TOK_STRING,
	TOK_REG,
	TOK_NUMBER,
	TOK_LNUMBER,
	TOK_DLABA,
	TOK_INDLABA,
	TOK_OPCODE,
	TOK_SEPARATOR,
	TOK_NEWLINE,
	TOK_COMMENT,
	TOK_MAX
}				t_token_type;


typedef struct s_token	t_token;

struct					s_token
{
	t_token			*next;
	t_token			*prev;
	char			*ptr;
	unsigned int		line;
	unsigned int		col;
	unsigned int		len;
	char			type;
	char			pad[3];
/*	union
	{
		
	}			u;*/
};

typedef struct			s_tokenizer
{
	unsigned int		line;
	unsigned int		col;
	unsigned int		i;
	unsigned int		len;
	unsigned int		line_start;
	int					ret;
}						t_tokenizer;

typedef	struct			s_env
{
	char				*file;
	t_token				*tokens;
	char				*dest;
	int					fd;
	char				pad[4];
}						t_env;

/*
** Mains
*/
void						print_lst(t_token *lst);
int						loader(t_env *env, char *file_name);

/*
** Tokenizer
*/
int						tokenizer(t_env *env);

char						get_tok_p_name(char *stream, unsigned int *i);
char						get_tok_p_com(char *stream, unsigned int *i);
char						get_tok_string(char *stream, unsigned int *i);
char						get_tok_reg(char *stream, unsigned int *i);
char						get_tok_number(char *stream, unsigned int *i);

static char					(*g_token_fts[NB_TOKENS_FUNCS])(char*, unsigned int*) = {
						[TOK_P_NAME - 1] = &get_tok_p_name,
						[TOK_P_COM - 1] = &get_tok_p_com,
						[TOK_STRING - 1] = &get_tok_string,
						[TOK_REG - 1] = &,
						[TOK_NUMBER - 1] = &,
						[TOK_LNUMBER - 1] = &,
						[TOK_DLABA - 1] = &,
						[TOK_INDLABA - 1] = &,
						[TOK_OPCODE - 1] = &,
						[TOK_SEPARATOR - 1] = &,
						[TOK_NEWLINE - 1] = &,
						[TOK_COMMENT - 1] = &
};

/*
** Errors reporting
*/
int						free_env(t_env *env);

#endif
