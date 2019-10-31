/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_launch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:48:03 by moguy             #+#    #+#             */
/*   Updated: 2019/10/31 18:21:41 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	launch_instruct(t_env *env, t_process *p)
{
	if (p->instruct.op <= OP_NONE || p->instruct.op >= OP_MAX)
		return ;
	convert_instruction(env, p);
}

void	create_instruct(t_env *env, t_process *p)
{
	p->instruct.op = get_mem_cell(env, p, 1, p->pc);
	load_args(env, p, encod_byte(p->instruct.op), direct_size(p->instruct.op));
	p->cycle_to_exec = wait_cycle(p->instruct.op);
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
	create_instruct(env, env->process);
	return (0);
}
