/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:13:39 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/19 23:41:34 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	swap_bytes(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
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
