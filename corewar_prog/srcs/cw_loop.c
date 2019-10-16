/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:56:12 by moguy             #+#    #+#             */
/*   Updated: 2019/10/16 11:07:38 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline int	check_delta(t_env *env, int new_lives, unsigned int count)
{
	unsigned int		nb_pl = 0;

	if (new_lives == 0)
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
	if (count + 1 == MAX_CHECKS)
	{
		env->cycle_to_die -=  CYCLE_DELTA;
		return (1);
	}
	return (0);
}

int		check_live(t_env *env)
{
	static unsigned int	prev_lives[4] = {0, 0, 0, 0};
	static unsigned int	nb_pl = 0;
	static unsigned int	count = 0;
	int					new_lives;

	nb_pl = env->nb_players;
	new_lives = 0;
	while (nb_pl >= 1)
	{

		if (env->nb_lives[nb_pl] > prev_lives[nb_pl])
			prev_lives[nb_pl] = env->nb_lives[nb_pl];
		else if (env->nb_lives[nb_pl] <= prev_lives[nb_pl] && (new_lives = -1))
			env->player[nb_pl - 1].dead = 1;
		nb_pl--;
	}
	if (check_delta(env, new_lives, count))
		count = 0;
	else
		count++;
	return (0);
}

void	init_arena(t_env *env)
{
	unsigned int	offset;
	unsigned int	num_pl;
	unsigned int	i;

	i = 0;
	num_pl = env->nb_players;
	offset = MEM_SIZE / env->nb_players;
	while (num_pl >= 1)
	{
		num_pl--;
		ft_memcpy(&env->arena[offset * i], env->player[num_pl].champ);
		env->player[num_pl].pc = offset * i;
		i++;
	}
}

int		process_cycle(t_env *env)
{
	unsigned int		nb_pl;

	nb_pl = env->nb_players;
	while (nb_pl >= 1 && !env->player[nb_pl - 1].dead)
	{
		nb_pl--;
	}
	return (0);
}

int		cw_loop(t_env *env)
{
	int					curr_cycle;

	curr_cycle = 0;
	init_arena(env);
	while (curr_cycle <= env->cycle_to_die && curr_cycle <= MAX_CYCLE)
	{
		while (curr_cycle < env->cycle_to_die && curr_cycle <= MAX_CYCLE)
		{
			if (process_cycle(env))
				return (1);
			curr_cycle++;
		}
		if (check_live(env))
			return (1);
		curr_cycle = 0;
	}
	return (0);
}
