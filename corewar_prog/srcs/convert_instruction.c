/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_instruction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:21:20 by moguy             #+#    #+#             */
/*   Updated: 2019/10/18 13:44:28 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		hex_convert(char a, char b, char c, char d)
{
	char	tab[4];

	tab[0] = a;
	tab[1] = b;
	tab[2] = c;
	tab[3] = d;
	return ((int)tab[0]);
}

int		nb_arg(char c)
{
	static int		arg_tab[NB_FUNC] = {1, 2, 2, 3, 3, 3, 3, 3, 1, 3, 3, 1,
									2, 3, 1, 1};

	return (arg_tab[c - 1]);
}

bool	carry_flag(char c)
{
	static bool		carry_tab[NB_FUNC] = {0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0,
									1, 1, 0, 0};

	return (carry_tab[c - 1]);
}

bool	direct_size(char c)
{
	static bool		direct_size[NB_FUNC] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
									0, 1, 1, 0};

	return (direct_size[c - 1]);
}

bool	encoding_byte(char c)
{
	static bool		encoding_tab[NB_FUNC] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0,
									1, 1, 0, 1};

	return (encoding_tab[c - 1]);
}

int		wait_cycle(char c)
{
	static int		wait[NB_FUNC] = {10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800,
									10, 50, 1000, 2};

	return (wait[c - 1]);
}

int		*convert_instruction(char c)
{
	static int		(*cw_func[NB_FUNC])(t_env *env, t_type arg[3],
			char encoding_byte) = {&live, &ld, &st, &add, &sub, &and, &or,
		&xor, &zjmp, &ldi, &sti, &fork, &lld, &lldi, &lfork, &aff};

	return (&cw_func[c - 1]);
}
