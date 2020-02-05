/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lives.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 21:08:32 by moguy             #+#    #+#             */
/*   Updated: 2020/02/05 10:00:45 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline t_process	*kill_process(t_env *env, t_process *tmp, t_process *p)
{
	if (env->opt[V] & (1 << 3))
	{
		printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
			tmp->rank, env->cycle_tot - tmp->alive, env->cycle_to_die);
	}
	if (tmp == env->process)
	{
		env->process = pop_lst(tmp, p);
		tmp = env->process;
	}
	else
		tmp = pop_lst(tmp, p);
	return (tmp);
}

static inline void		check_alive(t_env *env)
{
	t_process			*p[2];

	p[0] = env->process;
	p[1] = NULL;
	while (p[0])
	{
		if (!p[0]->next && env->cycle_tot - p[0]->alive >= env->cycle_to_die)
		{
			p[0] = kill_process(env, p[0], p[1]);
			if (p[1] == NULL)
				env->process = NULL;
		}
		else if (p[0]->next)
		{
			if (env->cycle_tot - p[0]->alive >= env->cycle_to_die)
				p[0] = kill_process(env, p[0], p[1]);
			else
			{
				p[1] = p[0];
				p[0] = p[0]->next;
			}
		}
		else
			return ;
	}
}

void					check_live(t_env *env)
{
	static unsigned int	count = 0;

	env->cycle_tot += env->cycle_curr;
	check_alive(env);
	if (env->curr_lives < NBR_LIVE && count < MAX_CHECKS)
		count++;
	else
		count = 0;
	if (env->curr_lives >= NBR_LIVE || count >= MAX_CHECKS)
		env->cycle_to_die -= CYCLE_DELTA;
	if ((env->opt[V] & (1 << 1))
			&& (count >= MAX_CHECKS
				|| env->curr_lives >= NBR_LIVE))
		printf("Cycle to die is now %d\n", env->cycle_to_die);
	if (count >= MAX_CHECKS)
		count = 0;
	env->curr_lives = 0;
}
