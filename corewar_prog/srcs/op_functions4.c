/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_functions4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 00:38:04 by moguy             #+#    #+#             */
/*   Updated: 2019/11/27 08:35:54 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				ldi(t_env *env, t_process *p)
{
	int32_t		val[3];

	val[0] = p->instruct.args[0].arg;
	val[1] = p->instruct.args[1].arg;
	val[2] = p->instruct.args[2].arg;
	if ((p->instruct.args[0].type == T_REG && (val[0] <= REG_NONE
					|| val[0] >= REG_MAX)) || (
					p->instruct.args[1].type == T_REG && (val[1] <= REG_NONE
			|| val[1] >= REG_MAX)) || val[2] <= REG_NONE || val[2] >= REG_MAX)
		return ;
	val[0] = get_arg_value(env, p, 0, true);
	val[1] = get_arg_value(env, p, 1, true);
	p->pctmp = p->pc + (uint16_t)((val[0] + val[1]) % IDX_MOD);
	p->r[val[2] - 1] = get_mem_cell(env, p, REG_SIZE);
}

void				aff(t_env *env, t_process *p)
{
	(void)env;
	if (p->instruct.args[0].arg > REG_NONE && p->instruct.args[0].arg < REG_MAX)
		ft_putchar((char)(p->r[p->instruct.args[0].arg - 1] % 256));
}
