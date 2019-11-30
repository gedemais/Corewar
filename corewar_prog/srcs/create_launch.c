/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_launch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:48:03 by moguy             #+#    #+#             */
/*   Updated: 2019/11/30 06:39:18 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	launch_instruct(t_env *env, t_process *p)
{
	if (p->instruct.op <= OP_NONE || p->instruct.op >= OP_MAX)
		return ;
	func_tab[p->instruct.op - 1].f(env, p);
}

void	create_instruct(t_env *env, t_process *p)
{
	p->pc = p->tpc;
	p->pctmp = p->pc;
	p->tpc++;
	p->instruct.op = (uint32_t)get_mem_cell(env, p, 1);
//	ft_putendl("");
//	ft_putnbr((int)p->instruct.op);
//	ft_putendl("");
	if (p->instruct.op <= OP_NONE || p->instruct.op >= OP_MAX)
		p->cycle_to_exec = 0;
	else
	{
		p->cycle_to_exec = (int)func_tab[p->instruct.op - 1].wait_cycles;
		load_args(env, p, (bool)func_tab[p->instruct.op - 1].encoding,
				(bool)func_tab[p->instruct.op - 1].direct);
	}
}

int		create_pro(t_env *env, unsigned int i, unsigned int ofset)
{
	if (env->process)
	{
		if (!(env->process = push_lst(env, env->player[i].id, (uint32_t)ofset)))
			return (error(LST_ERR, NULL, NULL));
	}
	if (!env->process)
	{
		if (!(env->process = new_lst(env->player[i].id, (uint32_t)ofset)))
			return (error(LST_ERR, NULL, NULL));
		env->process->rank = 1;
	}
	env->process->tpc = env->process->pc;
	create_instruct(env, env->process);
	return (0);
}
