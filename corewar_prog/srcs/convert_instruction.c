/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_instruction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:21:20 by moguy             #+#    #+#             */
/*   Updated: 2019/10/19 17:08:00 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

short	hex_conv2(char a, char b)
{
	char	tab[2];

	tab[0] = a;
	tab[1] = b;
	return ((short)tab[0]);
}

int		hex_conv4(char a, char b, char c, char d)
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

	return (arg_tab[(int)c - 1]);
}

int		wait_cycle(char c)
{
	static int		wait[NB_FUNC] = {10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800,
									10, 50, 1000, 2};

	return (wait[(int)c - 1]);
}

void	convert_instruction(t_env *env, t_process *process)
{
	static int		(*cw_func[NB_FUNC])(t_env*, t_process*) = {0};
/*	static int		(*cw_func[NB_FUNC])(t_env*, t_process*) = {&live, &ld, &st,
		&add, &sub, &and, &or, &xor, &zjmp, &ldi, &sti, &forky, &lld,
		&lldi, &lfork, &aff};*/

	(cw_func[(int)process->instruct.op_code - 1])(env, process);
}
