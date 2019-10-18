/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:53:56 by moguy             #+#    #+#             */
/*   Updated: 2019/10/18 13:59:59 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		create_first_process(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_players)
	{
		if (env->process)
		{
			if (!(process = push_lst(env, env->process, env->player[i]->id,
							env->player[i]->first->pc)))
				return (1);
		}
		if (!env->process)
			if (!(env->process = new_lst(env, env->player[i]->id,
							env->player[i]->first_pc)))
				return (1);
		i++;
	}
	return (0);
}

int		check_instruct(t_env *env)
{
	t_instruct		*tmp;

	if (!env->instruct)
		return (0);
	while (env->instruct->next)
	{
	//	apply_intruct(env, env->instruct);
		tmp = env->instruct;
		env->instruct = env->instruct->next;
		pop_instruct(tmp);
	}
//	apply_intruct(env, env->instruct);
	pop_instruct(tmp);
	return (0);
}

int		check_op(t_env *env, t_process *process)
{
	if ((process->op = env->arena[process->pc]) < 1 || process->op > 16)
		return (1);
	process->wait_cycle = wait_cycle(process->op - 1);	
	return (0);
}

int		load_op(t_env *env, t_process *process)
{
	int			len;
	uint16_t	pci : 12;
	
	pci = process->pc + 1;
	if (env->instruct)
		if (!(instruct = push_instruct(env, process)))
			return (-1);
	if (!(env->instruct))
		if (!(env->instruct = new_instruct(env, process)))
			return (-1);
	if (encoding_byte(process->op))
	{
	//	if (len = get_args(env, process, pci, direct_size(process->op)))
			return (-1);
	}
	else
	//	if (len = get_arg(env, process, pci, direct_size(process->op)))
			return (-1);
	process->carry = carry_flag(process->op);
	return (len);
}

int		add_instruction(t_env* env, t_process *process, int cur_cycle)
{
	t_process		*tmp;

	tmp = process;
	while (tmp->next)
	{
		if (tmp->wait_cycle == -1)
			check_op(env, tmp);
		else if ((tmp->wait_cycle -= 1) == 0)
		{
			if (process->pc = load_op(env, tmp) == -1)
				if (!(tmp = pop-lst(tmp, tmp, NULL)))
					return (1);
			check_op(env, tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}
