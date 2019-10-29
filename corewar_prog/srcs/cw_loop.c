/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:56:12 by moguy             #+#    #+#             */
/*   Updated: 2019/10/28 23:17:33 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline int	cycle_run(t_env *env, t_process *pro)
{
	t_process	*tmp;

	tmp = pro;
	while (tmp)
	{
		if ((tmp->cycle_to_exec -= 1) == 0)
		{
			launch_instruct(env, tmp);
			ft_memset(&tmp->instruct, 0, sizeof(t_instruct));
			create_instruct(env, tmp);
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			tmp = NULL;
	}
	return (0);
}

static inline int	init_arena(t_env *env)
{
	unsigned int	i;
	unsigned int	offset;

	i = 0;
	offset = MEM_SIZE / env->nb_pl;
	while (i < env->nb_pl)
	{
		ft_memcpy(&env->arena[offset * i], env->player[i].champ,
				env->player[i].size);
		if (create_pro(env, i, offset * i))
			return (1);
		i++;
	}
	return (0);
}

int		cw_loop(t_env *env)
{
	if (init_arena(env))
		return (1);
	while (env->cycle_curr <= env->cycle_to_die && env->cycle_tot <= MAX_CYCLE)
	{
		while (env->cycle_curr < env->cycle_to_die
			&& env->cycle_tot <= MAX_CYCLE)
		{
			if (cycle_run(env, env->process))
				return (1);
			env->cycle_curr++;
		}
		if (check_live(env))
			return (1);
	}
	return (0);
}
