/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_launch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:48:03 by moguy             #+#    #+#             */
/*   Updated: 2019/10/29 17:25:55 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		launch_instruct(t_env *env, t_process *p)
{
	if (p->instruct.op <= OP_NONE || p->instruct.op >= OP_MAX)
		return (0);
	else
		convert_instruction(env, p);
	p->carry = carry_flag(p->instruct.op); 
	return (0);
}

int		create_instruct(t_env *env, t_process *p)
{
	p->instruct.op = get_mem_cell(env, p, 1, p->pc);
	load_args(env, p, encod_byte(p->instruct.op), direct_size(p->instruct.op));
	p->cycle_to_exec = wait_cycle(p->instruct.op);
	return (0);
}

int		create_pro(t_env *env, unsigned int i, unsigned int offset)
{
	if (env->process)
	{
		if (!(env->process = push_lst(env->process, env->player[i].id,
					(uint16_t)offset)))
			return (error(LST_ERR, NULL, NULL));
	}
	if (!env->process)
		if (!(env->process = new_lst(env->player[i].id, (uint16_t)offset)))
			return (error(LST_ERR, NULL, NULL));
	if (create_instruct(env, env->process))
		return (1);
	return (0);
}
