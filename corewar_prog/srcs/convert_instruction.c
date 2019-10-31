/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_instruction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:21:20 by moguy             #+#    #+#             */
/*   Updated: 2019/10/30 17:37:53 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		wait_cycle(uint32_t c)
{
	static int		wait[NB_FUNC] = {10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800,
									10, 50, 1000, 2};

	if (c <= OP_NONE || c >= OP_MAX)
		return (0);
	return (wait[c - 1]);
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
