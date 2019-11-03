/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 20:01:11 by moguy             #+#    #+#             */
/*   Updated: 2019/11/02 23:05:05 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline char	hex_tab(uint8_t quartet)
{
	static char			hex_value[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

	return (hex_value[quartet]);
}

static inline void	print_octet(uint8_t hquartet, uint8_t lquartet, bool flush)
{
	static char			buffer[DUMP_LENGTH];
	static int			i = 0;
	static unsigned int	count = 0;

	buffer[i++] = hex_tab(hquartet);
	buffer[i++] = hex_tab(lquartet);
	count++;
	if (count == 64)
	{
		count = 0;
		buffer[i++] = '\n';
	}
	else
	{
		buffer[i++] = ' ';
		buffer[i++] = ' ';
	}
	if (flush)
	{
		buffer[i++] = '\n';
		buffer[i] = '\n';
		i = 0;
		write(1, &buffer[0], DUMP_LENGTH);
	}
}

void				dump(t_env *env)
{
	uint8_t				*arena;
	unsigned int		i;

	i = 0;
	arena = &env->arena[0];
	while (i < MEM_SIZE - 1)
	{
		print_octet((arena[i] >> 4) & 0xf, arena[i] & 0xf, false);
		i++;
	}
	print_octet((arena[i] >> 4) & 0xf, arena[i] & 0xf, true);
	env->cycle_to_dump = env->opt[DMP];
}
