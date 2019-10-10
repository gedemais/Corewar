/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:45:10 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/10 14:14:47 by demaisonc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline void	update_tok(char *stream, t_tokenizer *tok, unsigned int tmp)
{
	if (tok->ret == TOK_NEWLINE)
	{
		tok->line++;
		tok->line_start = tmp;
	}
	tok->col = tok->i - tok->line_start;
	if (tok->ret == TOK_COMMENT)
		while (stream[tok->i] != '\n')
			tok->i++;
	tok->len = tok->i - tmp;
}

static inline void	get_token_type(char *stream, t_tokenizer *tok)
{
	unsigned int	i;
	unsigned int	tmp;

	i = 0;
	tmp = tok->i;
	while (i < NB_TOKENS_FUNCS)
	{
		if ((tok->ret = g_token_fts[i](&stream[tok->i], &tok->i)))
		{
			update_tok(stream, tok, tmp);
			break ;
		}
		i++;
	}
}

static inline void	cross_whitespaces(char *stream, unsigned int *i)
{
	char	c;

	while (stream[*i])
	{
		c = stream[*i];
		if (c == '\n' || !ft_is_whitespace(c))
			break ;
		*i += 1;
	}
}

int		tokenizer(t_env *env)
{
	t_tokenizer	tok;

	ft_memset(&tok, 0, sizeof(t_tokenizer));
	while (env->file[tok.i])
	{
		cross_whitespaces(env->file, &tok.i);
		get_token_type(env->file, &tok);
		if (tok.ret == TOK_NONE)
			return (-1);
/*		if (token_pushfront(&env->tokens, token_lstnew(env->file, &tok)) != 0)
			return (-1);*/
	}
//	print_lst(env->tokens);
//	printf("\n");
	return (0);
}
