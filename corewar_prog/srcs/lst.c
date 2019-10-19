/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:08:31 by moguy             #+#    #+#             */
/*   Updated: 2019/10/19 17:21:34 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process	*new_lst(long long int id, uint16_t pc)
{
	t_process	*new;

	if (!(new = (t_process*)malloc (sizeof(t_process))))
		return (NULL);
	ft_memset(new, 0, sizeof(t_process));
	new->r[0] = (int)id;
	new->instruct.wait_cycle = -1;
	new->pc = pc;
	return (new);
}

t_process	*push_lst(t_process *process, long long int id, uint16_t pc)
{	
	t_process	*new;

	if (!(new = new_lst(id, pc)))
		return (NULL);
	new->next = process;
	return (new);
}

t_process	*pop_lst(t_process *process, t_process *tmp)
{
	if (tmp->next == NULL)
	{
		process = process->next;
		free(tmp);
		tmp = NULL;
		return (NULL);
	}
	return (process);
}
