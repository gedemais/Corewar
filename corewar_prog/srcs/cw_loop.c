/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:56:12 by moguy             #+#    #+#             */
/*   Updated: 2019/11/30 07:53:31 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline void	cycle_run(t_env *env, t_process *pro)
{
	t_process	*tmp;

	tmp = pro;
	env->cycle_curr++;
	if (env->opt[V] & (1 << 1))
		printf("It is now cycle %d\n", env->cycle_tot + env->cycle_curr);
	while (tmp && env->cycle_to_die > 0)
	{
		if (--tmp->cycle_to_exec <= 0)
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
}

static inline int	init_arena(t_env *env)
{
	unsigned int	i;
	unsigned int	offset;

	i = 0;
	env->cycle_to_dump = (int)env->opt[D];
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

static inline void	print_winner(t_env *env)
{
	unsigned int	i;

	i = env->last_live - 1;
	if (env->last_live == 0)
		printf("None of the players called live...LOSERS!!\n");
	else
		printf("Contestant %u, \"%s\", has won !\n",
			env->player[i].id, env->player[i].name);
}

int		cw_loop(t_env *env)
{
	if (init_arena(env))
		return (1);
	while (env->cycle_tot <= MAX_CYCLE && env->process)
	{
		if (env->cycle_to_die <= 0)
			cycle_run(env, env->process);
		while (env->cycle_curr < env->cycle_to_die
			&& env->cycle_tot <= MAX_CYCLE)
		{
			cycle_run(env, env->process);
			if (env->opt[D] != 0 && (env->cycle_to_dump -= 1) == 0)
			{
				dump(env);
				if (!env->opt[S])
					return (0);
			}
		}
		check_live(env);
	}
	print_winner(env);
	return (0);
}
