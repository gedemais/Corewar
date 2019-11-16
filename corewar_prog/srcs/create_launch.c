/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_launch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:48:03 by moguy             #+#    #+#             */
/*   Updated: 2019/11/08 04:09:48 by unknown          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	launch_instruct(t_env *env, t_process *p)
{
	if (p->instruct.op <= OP_NONE || p->instruct.op >= OP_MAX)
		return ;
	convert_instruction(env, p);
}

static inline int	check_instruct(t_env *env, t_process *p)
{
	if (p->instruct.op == OP_LIVE)
		if (p->instruct.args[0].arg > env->nb_pl || p->instruct.args[0].arg < 1)
			return (1);
	return (0);
}

void	create_instruct(t_env *env, t_process *p)
{
	p->instruct.op = get_mem_cell(env, p, 1, p->pc);
	p->cycle_to_exec = wait_cycle(p->instruct.op);
	load_args(env, p, encod_byte(p->instruct.op), direct_size(p->instruct.op));
	if (p->instruct.op != 0 && check_instruct(env, p))
	{
		p->instruct.op = 0;
		p->cycle_to_exec = 0;
	}
}

int		create_pro(t_env *env, unsigned int i, unsigned int offset)
{
	if (env->process)
	{
		if (!(env->process = push_lst(env->process, env->player[i].id,
					(u_int16_t)offset)))
			return (error(LST_ERR, NULL, NULL));
	}
	if (!env->process)
		if (!(env->process = new_lst(env->player[i].id, (u_int16_t)offset)))
			return (error(LST_ERR, NULL, NULL));
	create_instruct(env, env->process);
	return (0);
}
