/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:08:31 by moguy             #+#    #+#             */
/*   Updated: 2019/10/31 18:18:17 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process	*new_lst(uint32_t id, uint16_t pc)
{
	t_process	*new;

	if (!(new = (t_process*)malloc (sizeof(t_process))))
		return (NULL);
	ft_memset(new, 0, sizeof(t_process));
	new->r[0] = (int32_t)id;
	new->pc = pc;
	return (new);
}

t_process	*push_lst(t_process *process, uint32_t id, uint16_t pc)
{	
	t_process	*new;

	if (!(new = new_lst(id, pc)))
		return (NULL);
	new->next = process;
	return (new);
}

t_process	*pop_lst(t_process *process, t_process *prev)
{
	t_process	*tmp;

	tmp = process;
	if (tmp->next)
	{
		tmp = tmp->next;
		if (prev)
			prev->next = tmp;
		ft_memdel((void**)&process);
		return (tmp);
	}
	ft_memdel((void**)&process);
	if (prev)
		prev->next = NULL;
	return (NULL);
}
