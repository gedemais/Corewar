/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:08:18 by moguy             #+#    #+#             */
/*   Updated: 2019/11/03 00:17:25 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

bool	direct_size(u_int32_t c)
{
	static bool		direct_size[NB_FUNC] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
									0, 1, 1, 0};

	if (c <= OP_NONE || c >= OP_MAX)
		return (0);
	return (direct_size[c - 1]);
}

bool	encod_byte(u_int32_t c)
{
	static bool		encoding_tab[NB_FUNC] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0,
									1, 1, 0, 1};

	if (c <= OP_NONE || c >= OP_MAX)
		return (0);
	return (encoding_tab[c - 1]);
}
