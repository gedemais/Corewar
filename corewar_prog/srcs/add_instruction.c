/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:53:56 by moguy             #+#    #+#             */
/*   Updated: 2019/10/19 17:16:13 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int					check_dying_process(t_env *env)
{
	//kill process du player decede.
	return (0);
}

int					create_first_process(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_players)
	{
		if (env->process)
		{
			if (!(env->process = push_lst(env->process, env->player[i].id,
							env->player[i].first_pc)))
				return (1);
		}
		if (!env->process)
			if (!(env->process = new_lst(env->player[i].id,
							env->player[i].first_pc)))
				return (1);
		env->process->player = i;
		i++;
	}
	return (0);
}

static inline int	check_op(t_env *env, t_process *process)
{
	if ((process->instruct.op_code = env->arena[process->pc]) < 1
			|| process->instruct.op_code > 16)
		return (1);
	process->instruct.wait_cycle = wait_cycle(process->instruct.op_code - 1);	
	return (0);
}

int					add_instruction(t_env* env, t_process *process)
{
	t_process		*tmp;

	tmp = process;
	while (tmp->next)
	{
		if (tmp->instruct.wait_cycle == -1)
			check_op(env, tmp);
		else if ((tmp->instruct.wait_cycle -= 1) == 0)
		{
			if ((load_op(env, tmp)) == 0)
				if (!(tmp = pop_lst(tmp, tmp, NULL)))
					return (1);
			tmp->pc = tmp->pci;
			check_op(env, tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}
