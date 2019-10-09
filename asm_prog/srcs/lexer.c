/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:24:57 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/09 20:56:38 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_lex(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->type == LEX_HNAME)
			printf("HNAME|\n");
		if (tmp->type == LEX_HCOMMENT)
			printf("HCOMMENT|\n");
		if (tmp->type == LEX_LABEL)
			printf("LABEL|\n");
		if (tmp->type == LEX_NUMBER)
			printf("NUMBER|\n");
		if (tmp->type == LEX_LNUMBER)
			printf("LNUMBER|\n");
		if (tmp->type == LEX_DLABEL_CALL)
			printf("DLABEL_CALL|\n");
		if (tmp->type == LEX_IDLABEL_CALL)
			printf("IDLABEL_CALL|\n");
		if (tmp->type == TOK_NEWLINE)
			printf("NEWLINE\n");
		if (tmp->type == TOK_COLON)
			printf("COLON(%u)|\n", tmp->len);
		if (tmp->type == TOK_PERCENT)
			printf("PERCENT(%u)|\n", tmp->len);
		if (tmp->type == TOK_STRING)
			printf("STRING(%u)|\n", tmp->len);
		if (tmp->type == TOK_REG)
			printf("REGISTER(%u)|\n", tmp->len);
		if (tmp->type == TOK_COMMENT_CMD)
			printf("COMMENT_CMD(%u)|\n", tmp->len);
		if (tmp->type == TOK_NAME_CMD)
			printf("NAME_CMD(%u)|\n", tmp->len);
		if (tmp->type == TOK_SEPARATOR)
			printf("SEPARATOR|\n");
		if (tmp->type == TOK_COMMENT)
			printf("COMMENT|\n");
		if (tmp->type == TOK_OPCODE)
			printf("OPCODE(%u)|\n", tmp->len);
		if (tmp->type == TOK_WORD)
			printf("WORD(%u)|\n", tmp->len);
		if (tmp->type == TOK_NUMBER)
			printf("NUMBER(%u)|\n", tmp->len);
		tmp = tmp->next;
	}
	printf("\n");
}

static int	(*g_crushers[TOK_MAX - 1])(t_env*, t_token*) = {
	[TOK_NAME_CMD - 1] = &crush_name_cmd,
	[TOK_COMMENT_CMD - 1] = &crush_comment_cmd,
	[TOK_COMMENT - 1] = &crush_comment,
	[TOK_NEWLINE - 1] = &crush_newline,
	[TOK_COLON - 1] = NULL,
	[TOK_PERCENT - 1] = NULL,
	[TOK_SEPARATOR - 1] = NULL,
	[TOK_NUMBER - 1] = NULL,
	[TOK_OPCODE - 1] = NULL,
	[TOK_WORD - 1] = &crush_word,
	[TOK_STRING - 1] = NULL,
	[TOK_REG - 1] = NULL
};

int		lexer(t_env *env)
{
	t_token		*tmp;
	bool		changed;
	int			i;

	tmp = env->tokens;
	while (tmp->next)
	{
		changed = false;
		i = 0;
		while (i < TOK_MAX)
		{
			if (tmp->type == i + 1 && g_crushers[i])
			{
				if (g_crushers[i](env, tmp) != 0)
					return (-1);
				tmp = env->tokens;
				changed = true;
				break ;
			}
			i++;
		}
		if (changed)
			continue ;
		tmp = tmp->next;
	}
	print_lex(env->tokens);
	return (0);
}
