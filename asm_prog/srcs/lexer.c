/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:22:03 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/15 17:09:52 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline char	get_lexeme_type(t_env *env, t_token *tok)
{
	static char			(*g_lex_fts[NB_LEX_FUNCS])(t_env*, t_token*) = {
						&get_lex_name_prop,
						&get_lex_comment_prop,
						&get_lex_label,
						&get_lex_opcode};
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
	return (0);
}

static inline void	print_op_args(t_lexem lex)
{
	printf("Args :\n");
	if (lex.encoding & 128 && lex.encoding & 64)
		printf("indirect number (%lld)\n", lex.args[0].nb);
	if ((lex.encoding & 128) && !(lex.encoding & 64))
		printf("direct number (%lld)\n", lex.args[0].nb);
	if (!(lex.encoding & 128) && (lex.encoding & 64))
		printf("register (r%d)\n", lex.args[0].reg);

	if (lex.encoding & 32 && lex.encoding & 16)
		printf("indirect number (%lld)\n", lex.args[1].nb);
	if ((lex.encoding & 32) && !(lex.encoding & 16))
		printf("direct number (%lld)\n", lex.args[1].nb);
	if (!(lex.encoding & 32) && (lex.encoding & 16))
		printf("register (r%d)\n", lex.args[1].reg);
	
	if (lex.encoding & 8 && lex.encoding & 4)
		printf("indirect number (%lld)\n", lex.args[2].nb);
	if ((lex.encoding & 8) && !(lex.encoding & 4))
		printf("direct number (%lld)\n", lex.args[2].nb);
	if (!(lex.encoding & 8) && (lex.encoding & 4))
		printf("register (r%d)\n", lex.args[1].reg);
}

static inline void	print_lexem(t_lexem lex)
{
	switch (lex.type)
	{
		case LEX_NAME_PROP:
			printf("NAME_PROP (%s)\n", lex.args[0].str);
			break;
		case LEX_COMMENT_PROP:
			printf("COMMENT_PROP (%s)\n", lex.args[0].str);
			break;
		case LEX_LABEL:
			printf("LABEL\n");
			break;
		case LEX_OP:
			printf("OPCODE (%s)\n", g_opnames[(int)lex.opcode]);
			print_op_args(lex);
	//		print_byte_as_bits(lex.encoding);
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
	while (tmp && tmp->next)
	{
		if ((ret = get_lexeme_type(env, tmp)) <= LEX_NONE)
			return (-1);
		if (load_lexeme(env, lex, ret, &tmp) != 0)
			return (-1);
		lex++;
	}
	env->nb_lex = lex;
	for (unsigned int i = 0; i < lex ; i++)
		print_lexem(env->lexemes[i]);
	return (0);
}
