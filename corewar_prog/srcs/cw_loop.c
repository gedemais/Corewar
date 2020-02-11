/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:56:12 by moguy             #+#    #+#             */
/*   Updated: 2020/02/08 00:59:21 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline void	help_cycle_run(t_env *env)
{
	env->arg.str = "It is now cycle ";
	buffer_cor(env->arg, 0, 0);
	env->arg.n = env->cycle_tot + env->cycle_curr;
	buffer_cor(env->arg, 3, 0);
	env->arg.str = "\n";
	buffer_cor(env->arg, 0, 0);
}

static inline int	cycle_run(t_env *env, t_process *p)
{
	t_process		*tmp;

	tmp = p;
	env->cycle_curr++;
	if (env->opt[O_V] & (1 << 1))
		help_cycle_run(env);
	while (tmp)
	{
		if ((tmp->cycle_to_exec - 1) == 0)
			launch_instruct(env, tmp);
		if (--tmp->cycle_to_exec < 0)
		{
			ft_memset(&tmp->instruct, 0, sizeof(t_instruct));
			create_instruct(env, tmp);
			tmp->cycle_to_exec--;
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			tmp = NULL;
	}
	return (1);
}

int					init_arena(t_env *env)
{
	unsigned int	i;
	unsigned int	offset;

	i = 0;
	env->cycle_to_dump = (int)env->opt[O_D];
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
	env->arg.str = "Contestant ";
	buffer_cor(env->arg, 0, 0);
	if (env->last_live == 0)
		env->arg.u = env->player[env->nb_pl - 1].id;
	else
		env->arg.u = env->player[i].id;
	buffer_cor(env->arg, 2, 0);
	env->arg.str = ", \"";
	buffer_cor(env->arg, 0, 0);
	if (env->last_live == 0)
		env->arg.str = env->player[env->nb_pl - 1].name;
	else
		env->arg.str = env->player[i].name;
	buffer_cor(env->arg, 0, 0);
	env->arg.str = "\", has won !\n";
	buffer_cor(env->arg, 0, 0);
}

int					cw_loop(t_env *env)
{
	if (env->opt[O_S])
		dump(env);
	while (env->process && env->cycle_tot <= MAX_CYCLE)
	{
		if (env->cycle_to_die <= 0 && cycle_run(env, env->process))
			check_live(env);
		while (env->cycle_curr < env->cycle_to_die
				&& env->cycle_to_die > 0 && env->cycle_tot <= MAX_CYCLE)
		{
			cycle_run(env, env->process);
			if (env->cycle_curr >= env->cycle_to_die)
				check_live(env);
			if (env->opt[O_D] != 0 && (env->cycle_to_dump -= 1) == 0
					&& env->process)
			{
				dump(env);
				if (!env->opt[O_S])
					return (0);
			}
		}
		env->cycle_curr = 0;
	}
	print_winner(env);
	buffer_cor(env->arg, -1, 1);
	return (0);
}
