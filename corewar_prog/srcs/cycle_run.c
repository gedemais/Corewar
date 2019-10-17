/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:53:56 by moguy             #+#    #+#             */
/*   Updated: 2019/10/17 21:42:53 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		create_first_process(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_players)
	{
		if (env->process)
		{
			if (!(process = push_lst(env, env->process, env->player[i]->id,
							env->player[i]->first->pc)))
				return (1);
		}
		if (!env->process)
			if (!(env->process = new_lst(env, env->player[i]->id,
							env->player[i]->first_pc)))
				return (1);
		i++;
	}
	return (0);
}

int		check_cycle(t_env *env, int num_player)
{
	return (0);
}

int		add_instruction(t_env* env, t_process *process, int cur_cycle)
{
	t_process	*tmp;

	tmp = process;
	while (tmp->next)
	{
		if (tmp->wait_cycle == -1)
			check_pc(env);
		else if ((tmp->wait_cycle -= 1) == 0)
		{
			if (load_pc())
				kill_process();
			move_pc();
			check_pc();
		}
		tmp = tmp->next;
	}
	return (0);
}
