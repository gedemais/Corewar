/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:13:39 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/17 18:52:59 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	swap_short_bytes(short *val)
{
	char	swap[2];
	char	tmp;

	ft_memcpy(swap, val, IND_SIZE);
	tmp = swap[0];
	swap[0] = swap[1];
	swap[1] = tmp;
	ft_memcpy(val, swap, IND_SIZE);
}

int		reverse_int_bytes(int val)
{
	char	swap[4];
	char	tmp;

	ft_memcpy(swap, &val, DIR_SIZE);
	tmp = swap[0];
	swap[0] = swap[3];
	swap[3] = tmp;
	tmp = swap[1];
	swap[1] = swap[2];
	swap[2] = tmp;
	ft_memcpy(&val, swap, DIR_SIZE);
	return (val);
}

void	cross_whitespaces(char *stream, unsigned int *i)
{
	char	c;

	while (stream[*i])
	{
		c = stream[*i];
		if (c == '\n' || !ft_is_whitespace(c))
			break ;
		*i += 1;
	}
}

void	cross_whitespace(char *stream, unsigned int *i)
{
	while (stream[*i] && ft_is_whitespace(stream[*i]))
		*i += 1;
}

void	cross_names(char *stream, unsigned int *i)
{
	while (stream[*i] && (ft_isalnum(stream[*i]) || stream[*i] == '_'))
		*i += 1;
}
