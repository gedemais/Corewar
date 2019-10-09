/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:55:18 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/09 13:38:16 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_monos(char *stream, unsigned int *i)
{
	static char		monos[NB_MONOS] = {'\n', ',', '%', '#', ':'};
	static int		rets[NB_MONOS] = {TOK_NEWLINE, TOK_SEPARATOR,
										TOK_PERCENT, TOK_COMMENT, TOK_COLON};
	unsigned int	j;

	j = 0;
	while (j < NB_MONOS)
	{
		if (FCHAR == monos[j] && (*i += 1))
			return (rets[j]);
		j++;
	}
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
			return (TOK_OPCODE);
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
		return (TOK_COMMENT_CMD);
	}
	return (0);
}

int		get_word(char *stream, unsigned int *i)
{
	unsigned int	j;

	j = 0;
	if (!ft_isalnum(FCHAR) && FCHAR != '_')
		return (0);
	while (stream[j] && (ft_isalnum(stream[j]) || stream[j] == '_'))
		j++;
	*i += j;
	return (TOK_WORD);
}

int		get_numbers(char *stream, unsigned int *i)
{
	unsigned int	j;

	j = 1;
	if (!ft_isdigit(FCHAR) && FCHAR != '+' && FCHAR != '-')
		return (0);
	while (ft_isdigit(stream[j]))
		j++;
	*i += j;
	return (TOK_NUMBER);
}
