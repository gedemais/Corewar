/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 20:01:11 by moguy             #+#    #+#             */
/*   Updated: 2019/11/07 17:50:23 by unknown          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline char	hex_tab(u_int8_t quartet)
{
	static char			hex_value[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

	return (hex_value[quartet]);
}

static inline char 	hex_lines(int j)
{
	static u_int8_t		a = 0;
	static u_int8_t		b = 0;
	static u_int8_t		c = 0;
	static char		buffer[9] = {'0', 'x', '0', '0', '0', '0',
		' ', ':', ' '};

	if (j != 0)
	{
		if (j == 8)
			c += 4;
		return (buffer[j]);
	}
	if (a == 0 && b == 0 && c == 0)
		return (buffer[j]);
	if ((c % 16) == 0)
		b++;
	if ((b % 16) == 0 && (c % 16) == 0)
		a++;
	buffer[2] = hex_tab(a % 16);
	buffer[3] = hex_tab(b % 16);
	buffer[4] = hex_tab(c % 16);
	return (buffer[j]);
}

static inline void	print_octet(u_int8_t hquartet, u_int8_t lquartet, bool flush)
{
	static char			buffer[DUMP_LENGTH];
	static int			i = 0;
	static unsigned int		count = 0;
	int				j;

	if (count == 0 && (i += 9) && (j = -1))
		while (++j < 9)
			buffer[i - 9 + j] = hex_lines(j);
	buffer[i++] = hex_tab(hquartet);
	buffer[i++] = hex_tab(lquartet);
	count++;
	if (count == 64)
	{
		count = 0;
		buffer[i++] = '\n';
	}
	else
		buffer[i++] = ' ';
	if (flush)
	{
		i = 0;
		write(1, &buffer[0], DUMP_LENGTH);
	}
}

void				dump(t_env *env)
{
	u_int8_t				*arena;
	unsigned int		i;

	i = 0;
	arena = &env->arena[0];
	while (i < MEM_SIZE - 1)
	{
		print_octet((arena[i] >> 4) & 0xf, arena[i] & 0xf, false);
		i++;
	}
	print_octet((arena[i] >> 4) & 0xf, arena[i] & 0xf, true);
	if (env->opt[D] == false)
		write(1, "\n", 1);
	env->cycle_to_dump = env->opt[DMP];
}