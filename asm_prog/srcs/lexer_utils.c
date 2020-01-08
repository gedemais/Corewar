/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:55:31 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/08 15:06:35 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline size_t	arg_len(char *s)
{
	size_t	ret;

	ret = 0;
	while (is_label_char(s[ret]))
		ret++;
	return (ret);
}

char				find_op(char *op)
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

int					check_opcode_params(t_token *tok, int op, int nb_params)
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

