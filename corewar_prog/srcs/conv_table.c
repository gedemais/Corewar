/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:08:18 by moguy             #+#    #+#             */
/*   Updated: 2019/10/19 17:08:41 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

bool	carry_flag(char c)
{
	static bool		carry_tab[NB_FUNC] = {0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0,
									1, 1, 0, 0};

	return (carry_tab[(int)c - 1]);
}

bool	direct_size(char c)
{
	static bool		direct_size[NB_FUNC] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
									0, 1, 1, 0};

	return (direct_size[(int)c - 1]);
}

bool	encoding_byte(char c)
{
	static bool		encoding_tab[NB_FUNC] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0,
									1, 1, 0, 1};

	return (encoding_tab[(int)c - 1]);
}
