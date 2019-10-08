/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:48:51 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/08 17:02:21 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../../libft/libft.h"
# include <op.h>

# include <stdbool.h>
# include <stdio.h>

# define USAGE "usage: ./asm [champion.s]"
# define FILE_ERR_MSG "Invalid file or file name :"

# define BUFF_READ 65536

# define NB_TOKENS 4096
# define NB_OPS 16
# define NTOKFUNCS 5
# define FCHAR stream[0]

# define DEBUG_MODE false

typedef enum			e_token_type {
	TOK_NONE,
	TOK_NEWLINE, // "\n" //
	TOK_COLON, // ":" //
	TOK_PERCENT, // "%" //
	TOK_OP,
	TOK_KEY,
	TOK_LABEL,
	TOK_STRING, // "qqchose"
	TOK_REG, // "r[1-MAX_REG]" //
	TOK_COMMENT, // ".comment STRING"
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
	int					type;
	char				pad[4];
};

typedef struct			s_tokenizer
{
	unsigned int		line;
	unsigned int		col;
	unsigned int		i;
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

t_token					*token_lstnew(char *stream, t_tokenizer *tok);
int						token_pushfront(t_token **lst, t_token *new);
int						token_del_node(t_token *node);
int						token_free_lst(t_token *lst);

int						get_monos(char *stream, unsigned int *i);
int						get_strings(char *stream, unsigned int *i);
int						get_ops(char *stream, unsigned int *i);
int						get_regs(char *stream, unsigned int *i);
int						get_com_name(char *stream, unsigned int *i);


int						free_env(t_env *env);

#endif
