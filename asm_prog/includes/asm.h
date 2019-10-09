/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:48:51 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/09 19:36:43 by gedemais         ###   ########.fr       */
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

# define NB_TOKENS 4096
# define NB_MONOS 5
# define NB_OPS 16
# define NTOKFUNCS 8
# define FCHAR stream[0]

# define DEBUG_MODE true

typedef enum			e_token_type
{
	TOK_NONE,
	TOK_COMMENT, // '#' //
	TOK_NEWLINE, // '\n' //
	TOK_COLON, // ':' //
	TOK_PERCENT, // '%' //
	TOK_SEPARATOR, // ',' //
	TOK_NUMBER, // 0-9 only //
	TOK_OPCODE,
	TOK_WORD, // alphanumerics only //
	TOK_STRING, // "qqchose"
	TOK_REG, // "r[1-MAX_REG]" //
	TOK_COMMENT_CMD, // ".comment STRING"
	TOK_NAME_CMD, // ".name STRING"
	TOK_MAX,
	LEX_HNAME,
	LEX_HCOMMENT,
	LEX_LABEL,
	LEX_NUMBER,
	LEX_LNUMBER,
	LEX_DLABEL_CALL,
	LEX_IDLABEL_CALL,
	LEX_MAX
}						t_token_type;

typedef struct s_token	t_token;
typedef struct s_label	t_label;

struct					s_token
{
	t_token				*next;
	char				*ptr;
	unsigned int		line;
	unsigned int		col;
	unsigned int		len;
	int					type;
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

struct					s_label
{
	t_label				*next;
	char				*ptr;
	unsigned int		stick;
	unsigned int		len;
};

typedef	struct			s_env
{
	char				*file;
	t_token				*tokens;
	t_label				*labels;
	char				*dest;
	int					fd;
	char				pad[4];
}						t_env;

/*
** Mains
*/
void					print_lst(t_token *lst);
int						loader(t_env *env, char *file_name);

/*
** Tokenizer
*/
int						tokenizer(t_env *env);

t_token					*token_lstnew(char *stream, t_tokenizer *tok);
int						token_pushfront(t_token **lst, t_token *new);
int						token_snap_node(t_token **lst, t_token *node);
int						token_free_lst(t_token *lst);

int						get_monos(char *stream, unsigned int *i);
int						get_strings(char *stream, unsigned int *i);
int						get_ops(char *stream, unsigned int *i);
int						get_regs(char *stream, unsigned int *i);
int						get_com_name(char *stream, unsigned int *i);
int						get_word(char *stream, unsigned int *i);
int						get_numbers(char *stream, unsigned int *i);
int						get_comments(char *stream, unsigned int *i);

void	print_lex(t_token *lst);
/*
** Lexer
*/
int						lexer(t_env *env);

t_label					*label_lstnew(char *stream, t_token *tok);
int						label_pushfront(t_label **lst, t_label *new);
int						label_snap_node(t_label **lst, t_label *node);
int						label_free_lst(t_label *lst);
bool					find_label(t_label *lst, char *name, unsigned int len);

int						crush_comment(t_env *env, t_token *node);
int						crush_newline(t_env *env, t_token *node);
int						crush_colon(t_env *env, t_token *node);
int						crush_percent(t_env *env, t_token *node);
int						crush_word(t_env *env, t_token *node);
int						crush_comment_cmd(t_env *env, t_token *node);
int						crush_name_cmd(t_env *env, t_token *node);

/*
** Errors reporting
*/
int						unex_token_err(char *line, unsigned int nline, unsigned int col);
int						lexerr(char *ptr, unsigned int line, unsigned int col, char *msg);

int						free_env(t_env *env);

#endif
