/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:08:31 by moguy             #+#    #+#             */
/*   Updated: 2019/10/15 17:17:04 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process	*new_lst(t_env *env, unsigned int num_pl, uint16_t pc)
{
	t_process	*new;

	if (!(new = (t_process*)malloc (sizeof(t_process))))
		return (NULL);
	ft_memset(new, 0, sizeof(t_process));
	if (!(new->r = malloc(sizeof(REG_SIZE) * REG_NUMBER)))
	{
		free(new);
		return (NULL);
	}
	new->r[0] = env->player[num_pl].id;
	new->pc = pc;
	return (new);
}

t_process	*push_lst(t_env *env, t_process *process, unsigned int num_pl,
		unsigned int pc)
{	
	t_process	*new;
	t_process	*tmp;

	if (!(new = new_lst(env, num_pl, pc)))
		return (NULL);
	process->prev = new;
	tmp = process;
	new->next = tmp;
	return (new);
}

t_process	*pop_lst(t_process *process)
{
	t_process	*tmp;
	t_process	*tmp2;

	if (process->prev)
	{
		tmp = process->prev;
		if (process->next)
		{
			tmp2 = process->next;
			tmp->next = tmp2;
			tmp2->prev = tmp;
		}
		else
			tmp->next = NULL;
		ft_memdel(&process);
		return (tmp2);
	}
	else if (process->next)
	{
		tmp = process->next;
		tmp->prev = NULL;
	}
	ft_memdel(&process);
	return (NULL);
}
