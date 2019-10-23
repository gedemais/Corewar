/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:53:56 by moguy             #+#    #+#             */
/*   Updated: 2019/10/23 21:46:22 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

static inline int	kill_process(t_process *pro, unsigned int num_player)
{
	while (pro->next)
	{
		if (pro->player == num_player)
			if (!(pro = pop_lst(pro, pro)))
				return (1);
	}
	return (0);
}

int					check_dying_process(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_players)
	{
		if (env->player[i].dead == 1)
		{
			if (kill_process(env->process, i))
				return (1);
			env->player[i].dead = 2;
		}
		i++;
	}
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
	process->instruct.op_code = env->arena[process->pc];
	printf("op_code = %c\n", process->instruct.op_code + 48);
	if (process->instruct.op_code < 1 || process->instruct.op_code > 16)
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
			load_op(env, tmp);
			if (check_op(env, tmp))
				if (!(tmp = pop_lst(tmp, tmp)))
					return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
