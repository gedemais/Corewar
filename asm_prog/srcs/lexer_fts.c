/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:40:45 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/07 13:14:32 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	get_lex_name_prop(t_env *env, t_token *tok)
{
	static bool		done = false;
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
	if (!tok || tok->type != TOK_LABEL)
		return (0);
	if (!tok->next || ((tok->next->type == TOK_NEWLINE && check_after(tok->next)) && invalid_label_err(tok)))
		return (-1);
	if (tok->next->type != TOK_OPCODE && tok->next->type != TOK_NEWLINE)
		return (-1);
		tok = tok->next;
	while (tok && tok->type == TOK_NEWLINE)
		tok = tok->next;
	if (!tok || tok->type != TOK_OPCODE)
		return (-1);
	return (LEX_LABEL);
}

static inline size_t	arg_len(char *s)
{
	size_t	ret;

	ret = 0;
	while (is_label_char(s[ret]))
		ret++;
	return (ret);
}

char					find_op(char *op)
{
	unsigned int	i;
	size_t			size;
	size_t			op_size;

	i = 0;
	op_size = arg_len(op);
	while (i < NB_OPS)
	{
		size = ft_strlen(g_opnames[i]);
		if (size == op_size && ft_strncmp(op, g_opnames[i], op_size) == 0)
			return ((char)i);
		i++;
	}
	return (-1);
}

static inline int	check_opcode_params(t_token *tok, int op, int nb_params)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < 9 && tok && nb_params > 0)
	{
		j = 0;
		while (j < 3 && g_op_args[op][i + j])
		{
			if (tok->type == g_op_args[op][i + j])
			{
				nb_params--;
				break ;
			}
			j++;
		}
		if (!g_op_args[op][i + j] && invalid_op_parameter(tok, op))
			return (-1);
		tok = tok->next;
		if (nb_params > 0 && tok->type != TOK_SEPARATOR)
		{
			if (tok->type == TOK_NEWLINE)
				not_eno_args(tok, op);
			return (-1);
		}
		tok = nb_params > 0 ? tok->next : tok;
		if (nb_params > 0 && tok->type == TOK_NEWLINE && not_eno_args(tok, op))
			return (-1);
		i += 3;
	}
	if (tok->type != TOK_NEWLINE)
	{
		if (tok->type == TOK_SEPARATOR && (tok->next->type == TOK_REG || tok->next->type == TOK_LNUMBER || tok->next->type == TOK_NUMBER))
		{
			too_few_op_args(tok, op);
			return (-1);
		}
		expected_newline_err(tok);
		return (-1);
	}
	return (0);
}

char	get_lex_opcode(t_env *env, t_token *tok)
{
	unsigned int	i;
	int				op;
	int				nb_params;

	i = 0;
	(void)env;
	if (!tok || tok->type != TOK_OPCODE)
		return (0);
	while (ft_is_whitespace(*tok->ptr))
		tok->ptr++;
	if ((op = find_op(tok->ptr)) == -1 || (tok->next && tok->next->type == TOK_NEWLINE && not_eno_args(tok, op)))
		return (-1);
	tok = tok->next;
	nb_params = 0;
	while (i < 9 && g_op_args[op][i] != 0)
	{
		nb_params++;
		i += 3;
	}
	if (check_opcode_params(tok, op, nb_params) != 0)
		return (-1);
	return (LEX_OP);
}
