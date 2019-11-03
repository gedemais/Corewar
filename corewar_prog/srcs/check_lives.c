/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lives.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 21:08:32 by moguy             #+#    #+#             */
/*   Updated: 2019/11/03 07:34:03 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline t_process	*kill_process(t_env *env, t_process *tmp, t_process *p)
{
	if (env->verbose[2])
		printf("A process with the id %u died following a pitiful agony.\n",
				tmp->r[0]);
	tmp = pop_lst(tmp, p);
	return (tmp);
}

static inline void	check_alive(t_env *env)
{
	t_process			*tmp;
	t_process			*prev;
	
	tmp = env->process;
	prev = NULL;
	while (tmp)
	{
		if (tmp->next)
		{
			if (!tmp->alive)
				tmp = kill_process(env, tmp, prev);
			else
			{
				prev = tmp;
				tmp = tmp->next;
			}
		}
		else if (!tmp->next && !tmp->alive)
		{
			tmp = kill_process(env, tmp, prev);
			if (prev == NULL)
				env->process = NULL;
		}
	}
}

static inline void	verbose(t_env *env, unsigned int count)
{
	unsigned int	i;
	unsigned int	live_tot;

	i = 0;
	live_tot = 0;
	if (env->verbose[0] && count == 0)
	{
		printf("Cycle to die is decremented by cycle delta,");
		printf(" %d cycles before next cycle to die\n", env->cycle_to_die);	
	}
	if (env->verbose[4])
	{
		while (i < env->nb_pl)
		{
			printf("le joueur %u(%s) est a %d lives\n",
				env->player[i].id, env->player[i].name, env->live_pl[i]);
			live_tot += env->live_pl[i];
			i++;
		}
		if (live_tot > 1)
			printf("Pour un total de %d appels a la fonction live", live_tot);
		else
			printf("Pour un total de 1 appel a la fonction live");
	}
}

void				check_live(t_env *env)
{
	static unsigned int	count = 0;

	check_alive(env);
	if (env->curr_lives >= NBR_LIVE)
	{
		count = 0;
		env->cycle_to_die -= CYCLE_DELTA;
	}
	else
		count++;
	if (count == 10)
	{
		count = 0;
		env->cycle_to_die -= CYCLE_DELTA;
	}
	verbose(env, count);
	env->cycle_tot += env->cycle_curr;
	env->cycle_curr = 0;
	env->curr_lives = 0;
}
