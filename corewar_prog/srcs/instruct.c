/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:46:33 by moguy             #+#    #+#             */
/*   Updated: 2019/10/17 20:50:30 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_instruct	*new_instruct(t_process *process, t_type *arg)
{
	t_instruct	*new;

	if (!(new = (t_instruct*)malloc (sizeof(t_instruct))))
		return (NULL);
	ft_memset(new, 0, sizeof(t_instruct));
	new->process = process;
	new->arg[0] = arg[0];
	new->arg[1] = arg[1];
	new->arg[2] = arg[2];
	return (new);
}

t_instruct	*push_instruct(t_process *process, t_instruct *instruct,
		unsigned int num_pl, uint16_t pc)
{	
	t_instruct	*new;
	t_instruct	*tmp;

	if (!(new = new_instruct(env, process, pc)))
		return (NULL);
	instruct->prev = new;
	tmp = instruct;
	new->next = tmp;
	return (new);
}

t_instruct	*pop_instruct(t_instruct *instruct, t_instruct *tmp,
		t_instruct *tmp2)
{
	if (instruct->prev || instruct->next)
	{
		if (instruct->prev && instruct->next)
		{
			instruct = instruct->next;
			tmp2 = tmp->prev;
			instruct->prev = tmp2;
			tmp2->next = instruct;
		}
		else if (instruct->prev && !instruct->next)
		{
			instruct = instruct->prev;
			instruct->next = NULL;

		}
		else if (!instruct->prev && instruct->next)
		{
			instruct = instruct->next;
			instruct->prev = NULL;
		}
		ft_memdel((void**)&tmp);
		return (instruct);
	}
	ft_memdel((void**)&instruct);
	return (NULL);
}
