/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:48:51 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/17 18:27:04 by gedemais         ###   ########.fr       */
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
# define BLUE "\033[1;36m"
# define RED "\033[1;31m"
# define L_RED "\033[1;31m"
# define L_GREEN "\033[1;32m"
# define GRA "\033[1m"
# define STOP "\033[0m"

# define USAGE "usage: ./asm [champion.s]"
# define FILE_ERR_MSG "Invalid file or file name :"

# define BUFF_READ 65536
# define BUFF_WRITE 4096

# define FILE_SIZE 4096

# define LEX_COMB 32
# define LEX_DEPTH 4

# define HEADER_SIZE 2180

# define NB_OPS 16
# define NB_TOKENS_FUNCS 13
# define NB_LEX_FUNCS 4
# define NB_LEX_LOAD_FUNCS 4
# define FCHAR stream[0]

# define PADDING_VALUE 0

# define MAX_TYPE_SIZE 32

# define LBE_BUFFER 4

# define MAX_PARAM_NB 3

# define DEBUG_MODE false
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

static char						g_opcodes[NB_OPS] = {4, 16, 6, 12, 15, 2, 10, 13, 14, 1, 7, 3, 11, 5, 8, 9};


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
	LEX_LABEL,
	LEX_OP,
	LEX_MAX
}						t_lexemes_type;

typedef union		u_args
{
	char			*str;
	int				reg;
	unsigned int	stick;
	long long int	nb;
	bool			label;
}					t_args;

typedef struct			s_lexem
{
	unsigned int		start;
	char				opcode;
	char				type;
	char				encoding;
	char				pad;
	t_args				args[MAX_ARGS_NUMBER];
}						t_lexem;

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
	unsigned int		label;
	char				type;
	char				pad[3];
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
	char				*file_name;
	char				*p_name;
	char				*p_comment;
	t_token				*tokens;
	t_lexem				*lexemes;
	t_label				*labels;
	unsigned int		lab_i;
	unsigned int		nb_tokens;
	unsigned int		nb_labels;
	unsigned int		nb_lex;
	int					file_size;
	char				_pad[4];
}						t_env;

/*
** Mains
*/
void					print_lst(t_token *lst);
void print_byte_as_bits(char val);
int						loader(t_env *env, char *file_name);

/*
** Tokenizer
*/
int						tokenizer(t_env *env);
void					cross_whitespaces(char *stream, unsigned int *i);

int						init_labels(t_env *env);
int						add_label(t_env *env, unsigned int i);
bool					is_label(t_env *env, char *label);
int						find_label_index(t_label *labs, t_token *tok, unsigned int nb_labels);

t_token					*token_lstnew(t_env *env, t_tokenizer *tok);
int						token_pushfront(t_token **lst, t_token *new);
void					token_snap_node(t_token **lst, t_token *node);
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
											"add",
											"aff"
											"and"
											"fork"
											"lfork"
											"ld"
											"ldi"
											"lld"
											"lldi"
											"live"
											"or"
											"st"
											"sti"
											"sub"
											xor
											zjmp
*/

char					find_op(char *op);
char					encoding_byte(char byte, unsigned int param, int type);
bool					encoding_byte_pres(char type);

char					get_lex_name_prop(t_env *env, t_token *tok);
char					get_lex_comment_prop(t_env *env, t_token *tok);
char					get_lex_label(t_env *env, t_token *tok);
char					get_lex_opcode(t_env *env, t_token *tok);

bool					check_after(t_token *tok);
int						load_lex_name_prop(t_env *env, t_lexem *lex, t_token **tok);
int						load_lex_comment_prop(t_env *env, t_lexem *lex, t_token **tok);
int						load_lex_label(t_env *env, t_lexem *lex, t_token **tok);
int						load_lex_opcode(t_env *env, t_lexem *lex, t_token **tok);

static int				g_op_args[NB_OPS][MAX_ARGS_NUMBER * MAX_PARAM_NB] = {

						{TOK_REG, 0, 0, // Types possibles du premier param
						TOK_REG, 0, 0, // ____ second param
						TOK_REG, 0, 0},// add

						{TOK_REG, 0, 0,
						0, 0, 0,
						0, 0, 0}, // aff

						{TOK_REG, TOK_NUMBER, TOK_LNUMBER,
						TOK_REG, TOK_NUMBER, TOK_LNUMBER,
						TOK_REG, 0, 0}, // and
						
						{TOK_LNUMBER, 0, 0,
						0, 0, 0,
						0, 0, 0}, //fork
						
						{TOK_LNUMBER, 0, 0,
						0, 0, 0,
						0, 0, 0}, //lfork
						
						{TOK_NUMBER, TOK_LNUMBER, 0,
						TOK_REG, 0, 0,
						0, 0, 0}, //ld

						{TOK_REG, TOK_NUMBER, TOK_LNUMBER,
						TOK_REG, TOK_LNUMBER, 0,
						TOK_REG, 0, 0}, //ldi

						{TOK_NUMBER, TOK_LNUMBER, 0,
						TOK_REG, 0, 0,
						0, 0, 0}, //lld

						{TOK_REG, TOK_NUMBER, TOK_LNUMBER,
						TOK_NUMBER, TOK_REG, 0,
						TOK_REG, 0, 0}, //lldi

						{TOK_LNUMBER, 0, 0,
						0, 0, 0,
						0, 0, 0}, //live

						{TOK_REG, TOK_NUMBER, TOK_LNUMBER,
						TOK_REG, TOK_NUMBER, TOK_LNUMBER,
						TOK_REG, 0, 0}, // or

						{TOK_REG, 0, 0,
						TOK_REG, TOK_NUMBER, 0,
						0, 0, 0}, //st

						{TOK_REG, 0, 0,
						TOK_REG, TOK_LNUMBER, TOK_NUMBER,
						TOK_LNUMBER, TOK_REG},//sti

						{TOK_REG, 0, 0,
						TOK_REG, 0, 0,
						TOK_REG, 0, 0}, //sub

						{TOK_REG, TOK_LNUMBER, TOK_NUMBER,
						TOK_REG, TOK_LNUMBER, TOK_NUMBER,
						TOK_REG, 0, 0}, //xor

						{TOK_LNUMBER, 0, 0,
						0, 0, 0,
						0, 0, 0}//zjmp
};

/*
** Bytecode translating
*/
void					reverse_bits(char buff[LBE_BUFFER], int n);
char					rev_bits(char byte);

int						write_bytecode(t_env *env);
int						write_header(t_env *env, int fd);


/*
** Errors reporting
*/
int						invalid_syntax_err(t_env *env, t_tokenizer *tok);
int						expected_newline_err(t_token *tok);
int						invalid_op_parameter(t_token *tok, int op);
int						too_few_op_args(t_token *tok, int op);
int						not_eno_args(t_token *tok, int op);
int						invalid_label_err(t_token *tok);
int						undefined_label_err(t_env *env);
int						dup_label_err(char *label, unsigned int i, unsigned int first);
int						unknown_properity(char *stream);
int						property_error(char *file, t_token *tok);
int						missing_properity(bool name, bool comment);
int						dup_properity_err(char *file, unsigned int i);

int						free_env(t_env *env);

#endif
