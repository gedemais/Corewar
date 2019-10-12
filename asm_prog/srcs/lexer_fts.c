/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:40:45 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/12 18:20:45 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	get_lex_name_prop(t_env *env, t_token *tok)
{
	if (!tok || tok->type != TOK_P_NAME)
		return (0);
	if ((!tok->next || tok->next->type != TOK_STRING)
		&& !property_error(env->file, tok))
		return (-1);
	if (!tok->next->next || tok->next->next->type != TOK_NEWLINE)
	{
		expected_newline_err(tok);
		return (-1);
	}
	return (LEX_NAME_PROP);
}

char	get_lex_comment_prop(t_env *env, t_token *tok)
{
	if (!tok || tok->type != TOK_P_NAME)
		return (0);
	if ((!tok->next || tok->next->type != TOK_STRING)
		&& !property_error(env->file, tok))
		return (-1);
	if (!tok->next->next || tok->next->next->type != TOK_NEWLINE)
	{
		expected_newline_err(tok);
		return (-1);
	}
	return (LEX_COMMENT_PROP);
}
/*
char	get_lex_label(t_env *env, t_token *tok)
{
	
}

char	get_lex_opcode(t_env *env, t_token *tok)
{
	
}*/
