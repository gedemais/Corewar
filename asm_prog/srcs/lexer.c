/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:22:03 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/13 21:17:18 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline char	get_lexeme_type(t_env *env, t_token *tok)
{
	unsigned int	i;
	char			ret;

	i = 0;
	while (i < NB_LEX_FUNCS)
	{
		ret = g_lex_fts[i](env, tok);
		if (ret == -1)
			return (-1);
		if (ret > TOK_NONE)
			return (ret);
		i++;
	}
	return (0);
}

static inline int	load_lexeme(t_env *env, unsigned int lex, char type, t_token **tok)
{
	static int		(*load_lex_fts[NB_LEX_LOAD_FUNCS])(t_env*, t_lexem*, t_token**) = {
					&load_lex_name_prop,
					&load_lex_comment_prop,
					&load_lex_label,
					&load_lex_opcode};
	unsigned int	i;
	int				depth;

	i = 1;
	depth = 0;
	while (i < LEX_MAX)
	{
		if ((char)i == type && (depth = load_lex_fts[i - 1](env, &env->lexemes[lex], tok)) == -1)
			return (-1);
		if (depth > 0)
			break ;
		i++;
	}
	while ((*tok) && depth > 0)
	{
		(*tok) = (*tok)->next;
		depth--;
	}
	return (depth > 0 ? -1 : 0);
}

static inline void	print_lexem(t_lexem lex)
{
	switch (lex.type)
	{
		case LEX_NAME_PROP:
			printf("NAME_PROP\n");
			break;
		case LEX_COMMENT_PROP:
			printf("COMMENT_PROP\n");
			break;
		case LEX_LABEL:
			printf("LABEL\n");
			break;
		case LEX_OPCODE:
			printf("OPCODE\n");
			break;
	}
}

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
		sleep(1);
		if ((ret = get_lexeme_type(env, tmp)) <= LEX_NONE)
		{
			printf("Unexpected Token\n");
			fflush(stdout);
			// unex token
			return (-1);
		}
		if (load_lexeme(env, lex, ret, &tmp) != 0)
			return (-1);
		print_lexem(env->lexemes[lex]);
		lex++;
	}
	return (0);
}
