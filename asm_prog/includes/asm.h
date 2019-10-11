/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:48:51 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/11 20:06:01 by gedemais         ###   ########.fr       */
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

# define LEX_COMB 32
# define LEX_DEPTH 4

# define NB_OPS 16
# define NB_TOKENS_FUNCS 13
# define FCHAR stream[0]

# define DEBUG_MODE true
# define DBPRINT(str) if (DEBUG_MODE)\
						printf(str);\
						fflush(stdout);

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

typedef enum			e_token_type
{
	TOK_NONE,
	TOK_P_NAME,
	TOK_P_COM,
	TOK_STRING,
	TOK_REG,
	TOK_LABEL,
	TOK_NUMBER,
	TOK_LNUMBER,
	TOK_DLABA,
	TOK_INDLABA,
	TOK_OPCODE,
	TOK_SEPARATOR,
	TOK_NEWLINE,
	TOK_COMMENT,
	TOK_MAX
}						t_token_type;

typedef enum			e_lexemes_type
{
	LEX_NONE,
	LEX_NAME_PROP,
	LEX_COMMENT_PROP,
	LEX_OPCODE,
	LEX_MAX
}						t_lexemes_type;

static int				g_lexmatch[LEX_COMB][LEX_DEPTH] = {
						{TOK_P_NAME, TOK_STRING, TOK_NEWLINE, -1},
						{TOK_P_COM, TOK_STRING, TOK_NEWLINE, -1},
						{};
};


typedef struct			s_lexeme
{
	unsigned int		start;
	char				type;
	char			pad[3];
	union
	{
		char			*str;
		int				reg_a;
		int				reg_b;
		int				reg_c;
		int				nb;
		char			pad[3];
	}args;
}						t_lexeme;


typedef struct s_token	t_token;

struct					s_token
{
	t_token				*next;
	t_token				*prev;
	char				*ptr;
	unsigned int		line;
	unsigned int		col;
	unsigned int		len;
	unsigned int		index;
	char				type;
	char				pad[7];
};

typedef struct			s_tokenizer
{
	unsigned int		line;
	unsigned int		col;
	unsigned int		i;
	unsigned int		len;
	unsigned int		line_start;
	unsigned int		index;
	char				ret;
	char				pad[3];
}						t_tokenizer;

typedef struct			s_label
{
	char				*ptr;
	unsigned int		stick;
	unsigned int		len;
}						t_label;

typedef	struct			s_env
{
	t_tokenizer			tok;
	char				pad[4];
	char				*file;
	char				*dest;
	t_token				*tokens;
	t_lexeme			*lexemes;
	t_label				*labels;
	unsigned int		nb_labels;
	unsigned int		lab_i;
	unsigned int		nb_tokens;
	int					fd;
}						t_env;

/*
** Mains
*/
void					print_lst(t_token *lst);
int						loader(t_env *env, char *file_name);

/*
** Tokenizer
*/
int						tokenizer(t_env *env, t_tokenizer tok);
void					cross_whitespaces(char *stream, unsigned int *i);

int						init_labels(t_env *env);
int						add_label(t_env *env, unsigned int i);
bool					is_label(t_env *env, char *label);

t_token					*token_lstnew(t_env *env, t_tokenizer *tok);
int						token_pushfront(t_token **lst, t_token *new);
void					token_free_lst(t_token *lst);

char					get_tok_p_name(t_env *env, char *stream, unsigned int *i);
char					get_tok_p_com(t_env *env, char *stream, unsigned int *i);
char					get_tok_string(t_env *env, char *stream, unsigned int *i);
char					get_tok_reg(t_env *env, char *stream, unsigned int *i);
char					get_tok_number(t_env *env, char *stream, unsigned int *i);
char					get_tok_lnumber(t_env *env, char *stream, unsigned int *i);
char					get_tok_dlaba(t_env *env, char *stream, unsigned int *i);
char					get_tok_indlaba(t_env *env, char *stream, unsigned int *i);
char					get_tok_opcode(t_env *env, char *stream, unsigned int *i);
char					get_tok_separator(t_env *env, char *stream, unsigned int *i);
char					get_tok_newline(t_env *env, char *stream, unsigned int *i);
char					get_tok_comment(t_env *env, char *stream, unsigned int *i);
char					get_tok_label(t_env *env, char *stream, unsigned int *i);

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

/*
** Lexer
*/
int						lexer(t_env *env);

/*
** Errors reporting
*/
int						invalid_syntax_err(t_env *env, t_tokenizer *tok);
int						undefined_label_err(t_env *env, t_tokenizer *tok);




int						free_env(t_env *env);

#endif
