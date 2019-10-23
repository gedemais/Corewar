/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_instruction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:21:20 by moguy             #+#    #+#             */
/*   Updated: 2019/10/23 20:05:22 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

short	hex_conv2(char a, char b)
{
	return (a * PUI + b);	
}

int		hex_conv4(char a, char b, char c, char d)
{
	return (a * PUI3 + b * PUI2 + c * PUI + d);
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
/*	static int		(*cw_func[NB_FUNC])(t_env*, t_process*) = {&live, &ld, &st,
		&add, &sub, &and, &or, &xor, &zjmp, &ldi, &sti, &forky, &lld,
		&lldi, &lfork, &aff};

	(cw_func[(int)process->instruct.op_code - 1])(env, process);*/
	(void)env;
	(void)process;
}
