/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:08:18 by moguy             #+#    #+#             */
/*   Updated: 2019/10/29 21:37:13 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

bool	carry_flag(uint32_t c)
{
	static bool		carry_tab[NB_FUNC] = {0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0,
									1, 1, 0, 0};

	if (c <= OP_NONE || c >= OP_MAX)
		return (0);
	return (carry_tab[c - 1]);
}

bool	direct_size(uint32_t c)
{
	static bool		direct_size[NB_FUNC] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
									0, 1, 1, 0};

	if (c <= OP_NONE || c >= OP_MAX)
		return (0);
	return (direct_size[c - 1]);
}

bool	encod_byte(uint32_t c)
{
	static bool		encoding_tab[NB_FUNC] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0,
									1, 1, 0, 1};

	if (c <= OP_NONE || c >= OP_MAX)
		return (0);
	return (encoding_tab[c - 1]);
}
