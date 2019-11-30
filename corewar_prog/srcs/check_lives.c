/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lives.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 21:08:32 by moguy             #+#    #+#             */
/*   Updated: 2019/11/30 06:58:36 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline t_process	*kill_process(t_env *env, t_process *tmp, t_process *p)
{
	if (env->opt[V] & (1 << 3))
		printf("Process %d hasnt't lived for %d cycles (CTD %d) !\n",
				tmp->rank, env->cycle_tot - tmp->alive, env->cycle_to_die);
	if (tmp == env->process)
	{
		env->process = pop_lst(tmp, p);
		tmp = env->process;
	}
	else
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
			if (env->cycle_tot - tmp->alive > env->cycle_to_die)
				tmp = kill_process(env, tmp, prev);
			else
			{
				prev = tmp;
				tmp = tmp->next;
			}
		}
		else if (!tmp->next && env->cycle_tot - tmp->alive > env->cycle_to_die)
		{
			tmp = kill_process(env, tmp, prev);
			if (prev == NULL)
				env->process = NULL;
		}
		else
			return ;
	}
}

void				check_live(t_env *env)
{
	static unsigned int	count = 0;

	env->cycle_tot += env->cycle_curr;
	check_alive(env);
	if (env->curr_lives >= NBR_LIVE)
		count = 10;
	else if (count < 10)
		count++;
	if (count >= 10)
		env->cycle_to_die -= CYCLE_DELTA;
	if ((env->opt[V] & (1 << 1)) && count == 0)
		printf("Cycle to die is now %d\n", env->cycle_to_die);	
	env->cycle_curr = 0;
	env->curr_lives = 0;
}
