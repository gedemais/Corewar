/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lives.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 21:08:32 by moguy             #+#    #+#             */
/*   Updated: 2019/10/29 00:01:09 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline void	check_alive(t_process *tmp)
{
	t_process			*prev;
	
	prev = NULL;
	while (tmp)
	{
		if (tmp->next)
		{
			if (!tmp->alive)
				tmp = pop_lst(tmp, prev);
			else
			{
				prev = tmp;
				tmp = tmp->next;
			}
		}
		else
			if (!tmp->alive)
				tmp = pop_lst(tmp, prev);
	}
}

int					check_live(t_env *env)
{
	t_process			*tmp;
	static unsigned int	count = 0;

	tmp = env->process;
	check_alive(tmp);
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
	env->cycle_tot += env->cycle_curr;
	env->cycle_curr = 0;
	env->curr_lives = 0;
	return (0);
}
