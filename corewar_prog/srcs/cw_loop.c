/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:56:12 by moguy             #+#    #+#             */
/*   Updated: 2019/12/04 12:57:43 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline int	cycle_run(t_env *env, t_process *p)
{
	t_process	*tmp;

	tmp = p;
	env->cycle_curr++;
	if (env->opt[V] & (1 << 1))
		printf("It is now cycle %d\n", env->cycle_tot + env->cycle_curr);
	while (tmp && env->cycle_to_die > 0)
	{
		tmp->pctmp = tmp->pc;
		if ((tmp->instruct.op <= OP_NONE || tmp->instruct.op >= OP_MAX)
				&& (tmp->tpc = tmp->pc)
				&& ft_memset(&tmp->instruct, 0, sizeof(t_instruct)))
		{
			create_instruct(env, tmp);
			printf("P  %d | OP %d | %c%c %c%c %c%c %c%c %c%c\n", tmp->rank,
					tmp->instruct.op, hex_tab((env->arena[tmp->pc] >> 4) & 0xf),
					hex_tab(env->arena[tmp->pc] & 0xf),
					hex_tab((env->arena[tmp->pc + 1] >> 4) & 0xf),
					hex_tab(env->arena[tmp->pc + 1] & 0xf),
					hex_tab((env->arena[tmp->pc + 2] >> 4) & 0xf),
					hex_tab(env->arena[tmp->pc + 2] & 0xf),
					hex_tab((env->arena[tmp->pc + 3] >> 4) & 0xf),
					hex_tab(env->arena[tmp->pc + 3] & 0xf),
					hex_tab((env->arena[tmp->pc + 4] >> 4) & 0xf),
					hex_tab(env->arena[tmp->pc + 4] & 0xf));
		}
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
	return (1);
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
		printf("Contestant %u, \"%s\", has won !\n",
			env->player[env->nb_pl - 1].id, env->player[env->nb_pl - 1].name);
	else
		printf("Contestant %u, \"%s\", has won !\n",
			env->player[i].id, env->player[i].name);
}

int		cw_loop(t_env *env)
{
	if (init_arena(env))
		return (1);
	if (env->opt[S])
		dump(env);
	while (env->process && env->cycle_tot <= MAX_CYCLE)
	{
		if (env->cycle_to_die <= 0 && cycle_run(env, env->process))
				check_live(env);
		while (env->cycle_curr < env->cycle_to_die
			&& env->cycle_tot <= MAX_CYCLE)
		{
			cycle_run(env, env->process);
			if (env->cycle_curr >= env->cycle_to_die)
				check_live(env);
			if (env->opt[D] != 0 && (env->cycle_to_dump -= 1) == 0)
			{
				dump(env);
				if (!env->opt[S])
					return (0);
			}
		}
		env->cycle_curr = 0;
	}
	print_winner(env);
	return (0);
}
