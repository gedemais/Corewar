/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:56:12 by moguy             #+#    #+#             */
/*   Updated: 2019/10/31 18:30:49 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline void	cycle_run(t_env *env, t_process *pro)
{
	t_process	*tmp;

	tmp = pro;
	if (env->verbose[2])
		printf("%d cycles have been done.\n", env->cycle_tot + env->cycle_curr);
	while (tmp)
	{
		tmp->cycle_to_exec--;
		if (tmp->cycle_to_exec == 0)
		{
			launch_instruct(env, tmp);
			ft_memset(&tmp->instruct, 0, sizeof(t_instruct));
			create_instruct(env, tmp);
		//	aff_process(tmp, false);
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			tmp = NULL;
	}
}

static inline int	init_arena(t_env *env)
{
	unsigned int	i;
	unsigned int	offset;

	i = 0;
	env->cycle_to_dump = env->opt[DMP];
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
	unsigned int	i;
	
	if (init_arena(env))
		return (1);
	//aff_env(env, 1);
	while (env->cycle_curr <= env->cycle_to_die && env->cycle_tot <= MAX_CYCLE
			&& env->process)
	{
		while (env->cycle_curr < env->cycle_to_die
			&& env->cycle_tot <= MAX_CYCLE)
		{
			env->cycle_curr++;
			cycle_run(env, env->process);
			if (env->opt[DMP] != 0 && (env->cycle_to_dump -= 1) == 0)
				dump(env);
		}
		check_live(env);
	}
	i = 0;
	while (i < env->nb_pl || env->player[i].id == env->last_live)
		i++;
	printf("le joueur %u(%s) a gagne\n",
			env->player[i].id, env->player[i].name);
	return (0);
}
