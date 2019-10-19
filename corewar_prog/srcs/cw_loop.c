/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:56:12 by moguy             #+#    #+#             */
/*   Updated: 2019/10/19 17:13:11 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline int	check_delta(t_env *env, int victim)
{
	unsigned int		nb_pl = 0;

	if (victim == 1)
		return (0);
	while (nb_pl < env->nb_players)
	{
		new_lives += env->nb_lives[nb_pl];
		nb_pl++;
	}
	if (new_lives >= NBR_LIVE)
	{
		env->cycle_to_die -=  CYCLE_DELTA;
		return (1);
	}
	return (0);
}

static inline int	check_live(t_env *env)
{
	static unsigned int	prev_lives[4] = {0, 0, 0, 0};
	static unsigned int	nb_pl = 0;
	static unsigned int	count = 0;
	bool				victim;

	victim = false;
	nb_pl = env->nb_players;
	while (nb_pl >= 1)
	{

		nb_pl--;
		if (env->nb_lives[nb_pl] > prev_lives[nb_pl])
			prev_lives[nb_pl] = env->nb_lives[nb_pl];
		else if (env->nb_lives[nb_pl] <= prev_lives[nb_pl] && (victim = true))
			env->player[nb_pl].dead = 1;
	}
	if (check_delta(env, victim))
		count = 0;
	else
		count++;
	if (count == MAX_CHECKS && (count = 0))
		env->cycle_to_die -=  CYCLE_DELTA;
	env->cycle += env->curr_cycle;
	env->curr_cycle = 0;
	check_dying_process(env);
	return (0);
}

static inline void	init_arena(t_env *env)
{
	unsigned int	offset;
	unsigned int	num_pl;
	unsigned int	i;

	i = 0;
	num_pl = env->nb_players;
	offset = MEM_SIZE / num_pl;
	while (num_pl >= 1)
	{
		num_pl--;
		ft_memcpy(&env->arena[offset * i], env->player[num_pl].champ,
				env->player[num_pl].siz);
		env->player[num_pl].first_pc = (uint16_t)(offset * i);
		i++;
	}
}

static inline int	cycle_run(t_env *env)
{
	unsigned int		i;

	i = 0;
	while (i < env->nb_players)
	{
		if (!env->player[i].dead)
		{
			if (add_instruction(env, env->process))
				return (1);
			convert_instruction(env, env->process);
		}

		i++;
	}
	return (0);
}

int		cw_loop(t_env *env)
{
	init_arena(env);
	if (create_first_process(env))
		return (1);
	while (env->curr_cycle <= env->cycle_to_die && env->curr_cycle <= MAX_CYCLE)
	{
		while (env->curr_cycle < env->cycle_to_die
				&& env->curr_cycle <= MAX_CYCLE)
		{
			if (cycle_run(env))
				return (1);
			env->curr_cycle++;
		}
		if (check_live(env))
			return (1);
	}
	return (0);
}
