/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:22:03 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/12 20:45:06 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline char	get_lexeme_type(t_env *env, t_token *tok)
{
	unsigned int	i;
	char			ret;

	i = 0;
	while (i < LEX_MAX)
	{
		ret = g_lex_fts[i](env, tok);
		if (ret == -1)
			return (-1);
		if (ret != TOK_NONE)
			return (ret);
		i++;
	}
	return (0);
}
/*
static inline int	load_lexeme(t_lexeme lex, char type, t_token **tok)
{
	
}*/

int		lexer(t_env *env)
{
	t_token			*tmp;
	unsigned int	lex;
	char			ret;

	lex = 0;
	tmp = env->tokens;
	if (!(env->lexemes = (t_lexem*)malloc(sizeof(t_lexem) * env->nb_tokens)))
		return (-1);
	ft_memset(env->lexemes, 0, sizeof(t_lexem) * env->nb_tokens);
	while (tmp)
	{
		if ((ret = get_lexeme_type(env, tmp)) <= LEX_NONE)
		{
			// unex token
			return (-1);
		}
//		if (load_lexeme(env->lexemes[lex], ret, &tmp) != 0)
//			return (-1);
		lex++;
	}
	return (0);
}
