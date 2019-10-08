/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:55:18 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/08 16:24:21 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_monos(char *stream, unsigned int *i)
{
	if (FCHAR == '\n' && (*i += 1))
		return (TOK_NEWLINE);
	else if (FCHAR == '%' && (*i += 1))
		return (TOK_PERCENT);
	return (0);
}

int		get_strings(char *stream, unsigned int *i)
{
	unsigned int	j;

	j = 1;
	if (FCHAR != '"')
		return (0);
	while (stream[j] && stream[j] != '"' && stream[j] != '\n')
		j++;
	if (stream[j] == '"')
	{
		*i += j + 1;
		return (TOK_STRING);
	}
	return (0);
}

int		get_ops(char *stream, unsigned int *i)
{
	static char	*ops_names[NB_OPS] = {"lfork", "sti", "fork", "lld", "ld",
				"add", "zjmp", "sub", "ldi", "or", "st", "aff", "live",
				"xor", "lldi", "and"};
	int				j;
	size_t			len;
	size_t			nlen;

	len = ft_strlen(stream);
	j = -1;
	while (++j < NB_OPS && (nlen = ft_strlen(ops_names[j])))
		if (nlen < len && ft_strncmp(stream, ops_names[j], nlen) == 0)
		{
			*i += nlen;
			return (TOK_OP);
		}
	return (0);
}

int		get_regs(char *stream, unsigned int *i)
{
	long long int	reg_nb;
	unsigned int	j;

	j = 1;
	if (FCHAR != 'r')
		return (0);
	while (stream[j] && ft_isdigit(stream[j]))
		j++;
	if (j > 2 || (reg_nb = ft_atoi(&stream[1])) <= 0 || reg_nb > REG_NUMBER)
		return (0);
	*i += j;
	return (TOK_REG);
}

int		get_com_name(char *stream, unsigned int *i)
{
	size_t			len;
	size_t			com_len;
	size_t			name_len;

	if (FCHAR != '.')
		return (0);
	len = ft_strlen(stream);
	name_len = ft_strlen(NAME_CMD_STRING);
	com_len = ft_strlen(COMMENT_CMD_STRING);
	if (len > name_len && !ft_strncmp(stream, NAME_CMD_STRING, name_len))
	{
		*i += name_len;
		return (TOK_NAME);
	}
	if (len > com_len && !ft_strncmp(stream, COMMENT_CMD_STRING, com_len))
	{
		*i += com_len;
		return (TOK_COMMENT);
	}
	return (0);
}
