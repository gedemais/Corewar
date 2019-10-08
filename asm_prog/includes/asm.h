/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:48:51 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/08 21:20:37 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../../libft/libft.h"
# include <op.h>

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
# define NTOKFUNCS 6
# define FCHAR stream[0]

# define DEBUG_MODE true

typedef enum			e_token_type {
	TOK_NONE,
	TOK_COMMENT, // '#' //
	TOK_NEWLINE, // '\n' //
	TOK_COLON, // ':' //
	TOK_PERCENT, // '%' //
	TOK_SEPARATOR, // ',' //
	TOK_NUMBER, // 0-9 only //
	TOK_WORD, // alphanumerics only //
	TOK_STRING, // "qqchose"
	TOK_REG, // "r[1-MAX_REG]" //
	TOK_COMMENT_CMD, // ".comment STRING"
	TOK_NAME, // ".name STRING"
	TOK_MAX
}						t_token_type;

typedef struct s_token	t_token;

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
int						loader(t_env *env, char *file_name);

/*
** Tokenizer
*/
int						tokenizer(t_env *env);
int						unex_token_err(char *line, unsigned int nline, unsigned int col);

t_token					*token_lstnew(char *stream, t_tokenizer *tok);
int						token_pushfront(t_token **lst, t_token *new);
int						token_snap_node(t_token **lst, t_token *node);
int						token_free_lst(t_token *lst);

int						get_monos(char *stream, unsigned int *i);
int						get_strings(char *stream, unsigned int *i);
//int						get_ops(char *stream, unsigned int *i);
int						get_regs(char *stream, unsigned int *i);
int						get_com_name(char *stream, unsigned int *i);
int						get_word(char *stream, unsigned int *i);
int						get_numbers(char *stream, unsigned int *i);


int						free_env(t_env *env);

#endif
