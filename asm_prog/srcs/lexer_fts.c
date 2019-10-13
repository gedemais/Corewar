/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:40:45 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/13 17:51:53 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	get_lex_name_prop(t_env *env, t_token *tok)
{
	static bool		done = false;
	printf("get_lex_name_prop\n");
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
	if (done)
		return (-1);
	done = true;
	return (LEX_NAME_PROP);
}

char	get_lex_comment_prop(t_env *env, t_token *tok)
{
	static bool		done = false;
	printf("get_lex_comment_prop\n");

	if (!tok || tok->type != TOK_P_COM)
		return (0);
	if ((!tok->next || tok->next->type != TOK_STRING)
		&& !property_error(env->file, tok))
		return (-1);
	if (!tok->next->next || tok->next->next->type != TOK_NEWLINE)
	{
		expected_newline_err(tok);
		return (-1);
	}
	if (done)
		return (-1);
	done = true;
	return (LEX_COMMENT_PROP);
}

char	get_lex_label(t_env *env, t_token *tok)
{
	(void)env;
	printf("get_lex_label_prop\n");
	if (!tok || tok->type != TOK_LABEL)
		return (0);
	if (!tok->next
		|| (tok->next->type != TOK_OPCODE && tok->next->type != TOK_NEWLINE))
		return (-1);
		tok = tok->next;
	while (tok && tok->type == TOK_NEWLINE)
		tok = tok->next;
	if (!tok || tok->type != TOK_OPCODE)
		return (-1);
	return (LEX_LABEL);
}

static inline char	find_op(char *op)
{
	unsigned int	i;
	size_t			size;
	size_t			op_size;

	i = 0;
	op_size = ft_strlen(op);
	while (i < NB_OPS)
	{
		printf("%s\n", g_opnames[i]);
		size = ft_strlen(g_opnames[i]);
		if (op_size == size && !ft_strncmp(op, g_opnames[i], op_size))
			return ((char)i);
		i++;
	}
	return (0);
}

static inline int	check_opcode_params(t_token *tok, int op, int nb_params)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (tok && tok->type != TOK_NEWLINE && nb_params > 0)
	{
		j = 0;
		while (j < 3 && tok->type != g_op_args[op][i + j] // Looking for the param type
			&& g_op_args[op][i + j] != 0)
			j++;
		if (j >= 3 || !g_op_args[op][i + j]) // Error if not found
			return (-1);
		i += 3;
		nb_params--;
		tok = tok->next;
		if (nb_params > 0 && tok->type != TOK_SEPARATOR)
			return (-1);
		tok = tok->next;
	}
	return (0);
}

char	get_lex_opcode(t_env *env, t_token *tok)
{
	unsigned int	i;
	int				op;
	int				nb_params;

	op = -1;
	i = 0;
	(void)env;
	printf("get_lex_opcode\n");
	if (!tok || tok->type != TOK_OPCODE)
		return (0);
	while (ft_is_whitespace(*tok->ptr))
		tok->ptr++;
	if ((op = find_op(tok->ptr)) == 0)
		return (-1);
	nb_params = 0;
	while (g_op_args[op][i] != 0)
	{
		nb_params++;
		i += 3;
	}
	if (check_opcode_params(tok, op, nb_params) != 0)
		return (-1);
	return (LEX_OPCODE);
}
