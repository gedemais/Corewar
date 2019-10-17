/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:08:31 by moguy             #+#    #+#             */
/*   Updated: 2019/10/16 13:17:27 by moguy            ###   ########.fr       */
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
	new->r[0] = (int)env->player[num_pl].id;
	new->pc = pc;
	return (new);
}

t_process	*push_lst(t_env *env, t_process *process, unsigned int num_pl,
		uint16_t pc)
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

t_process	*pop_lst(t_process *process, t_process *tmp, t_process *tmp2)
{
	if (process->prev || process->next)
	{
		if (process->prev && process->next)
		{
			process = process->next;
			tmp2 = tmp->prev;
			process->prev = tmp2;
			tmp2->next = process;
		}
		else if (process->prev && !process->next)
		{
			process = process->prev;
			process->next = NULL;

		}
		else if (!process->prev && process->next)
		{
			process = process->next;
			process->prev = NULL;
		}
		ft_memdel((void**)&tmp);
		return (process);
	}
	ft_memdel((void**)&process);
	return (NULL);
}
