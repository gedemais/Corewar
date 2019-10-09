/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_crushers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:53:38 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/09 20:56:05 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
/*
static inline t_token	*next_node(t_tokenunsigned int index)
{
	t_token			*tmp;
	unsigned int	i;

	tmp = node;
	i = 0;
	while (tmp->next && i < index)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}*/

int		crush_comment(t_env *env, t_token *node)
{
	if (!node->next || node->next->type != TOK_NEWLINE)
		return (-1);
	return (token_snap_node(&env->tokens, node));
}

int		crush_newline(t_env *env, t_token *node)
{
	return (node->next ? token_snap_node(&env->tokens, node) : 0);
}

int		crush_colon(t_env *env, t_token *node)
{
	(void)env;
	(void)node;
	return (0);
}

int		crush_percent(t_env *env, t_token *node)
{
	t_token	*ptr;

	ptr = node->next;
	if (ptr->type == TOK_COLON && ptr->next->type == LEX_LABEL
		&& find_label(env->labels, ptr->next->ptr, ptr->next->len))
	{
		ptr->next->type = LEX_LNUMBER;
		ptr->next->ptr = node->ptr;
		ptr->next->len += 2;
		if (token_snap_node(&env->tokens, node) != 0
			|| token_snap_node(&env->tokens, ptr) != 0)
			return (-1);
	}
	else if (ptr->type == TOK_NUMBER)
	{
		ptr->type = LEX_LNUMBER;
		ptr->ptr = node->ptr;
		ptr->len++;
		if (token_snap_node(&env->tokens, node) != 0)
			return (-1);
	}
	return (0);
}

int		crush_word(t_env *env, t_token *node)
{
	if (node->next && node->next->type == TOK_COLON)
	{
		node->type = LEX_LABEL;
		node->len += node->next->len;
		if (label_pushfront(&env->labels, label_lstnew(env->file, node))
			|| token_snap_node(&env->tokens, node->next))
			return (-1);
	}
	return (0);
}

int		crush_comment_cmd(t_env *env, t_token *node)
{
	if (!node->next || node->next->type != TOK_STRING
		|| node->next->next->type != TOK_NEWLINE)
	{
		lexerr(node->ptr, node->line, node->col,
			node->next ? COMMENT_CMD_E0 : COMMENT_CMD_E1);
		return (-1);
	}
	node->type = LEX_HCOMMENT;
	node->len += node->next->len;
	if (token_snap_node(&env->tokens, node->next))
		return (-1);
	return (0);
}

int		crush_name_cmd(t_env *env, t_token *node)
{
	if (!node->next || node->next->type != TOK_STRING
		|| node->next->next->type != TOK_NEWLINE)
	{
		lexerr(node->ptr, node->line, node->col,
			node->next ? NAME_CMD_E0 : NAME_CMD_E1);
		return (-1);
	}
	node->type = LEX_HNAME;
	node->len += node->next->len;
	if (token_snap_node(&env->tokens, node->next))
		return (-1);
	return (0);
}
