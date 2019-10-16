/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_instruction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:21:20 by moguy             #+#    #+#             */
/*   Updated: 2019/10/15 17:30:37 by moguy            ###   ########.fr       */
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
	return ((int)tab);
}

int		nb_arg(char c)
{
	static int		arg_tab[16] = {1, 2, 2, 3, 3, 3, 3, 3, 1, 3, 3, 1,
									2, 3, 1, 1};

	return (arg_tab[c - 1]);
}

bool	carry_flag(char c)
{
	static bool		carry_tab[16] = {0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0,
									1, 1, 0, 0};

	return (carry_tab[c - 1]);
}

bool	encoding_byte(char c)
{
	static bool		encoding_tab[16] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0,
									1, 1, 0, 1};

	return (encoding_tab[c - 1]);
}

void	*convert_instruction(char c, t_env *env)
{
	static void		(*cw_func[NB_FUNC])(t_env*) = {&live, &ld, &st, &add,
			&sub, &and, &or, &xor, &zjmp, &ldi, &sti, &fork, &lld, &lldi,
			&lfork, &aff};

	return (&cw_func_[c - 1](env));
}
