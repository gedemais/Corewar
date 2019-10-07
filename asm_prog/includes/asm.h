/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:48:51 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/08 00:53:59 by demaisonc        ###   ########.fr       */
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

# define NB_TOKENS 1024

# define DEBUG_MODE true

typedef enum		e_token_type {
	TOK_NONE,
	TOK_NEWLINE, // "\n"
	TOK_COLON, // ":"
	TOK_PERCENT, // "%"
	TOK_OP,
	TOK_STRING, // "qqchose"
	TOK_REG, // "r[1-MAX_REG]"
	TOK_COMMENT, // ".comment STRING"
	TOK_NAME, // ".name STRING"
	TOK_MAX
}					t_token_type;

typedef struct		s_token
{
	char		*ptr;
	t_token_type	type;
	unsigned int	line;
}					t_token;

typedef	struct	s_env
{
	char		*file;
	t_token		*tokens;
	char		*dest;
	int			fd;
	char		pad[4];
}				t_env;

int				loader(t_env *env, char *file_name);
int				tokenizer(t_env *env);
int				get_token_type(char *stream, unsigned int *j, unsigned int *line);
int				free_env(t_env *env);

#endif
