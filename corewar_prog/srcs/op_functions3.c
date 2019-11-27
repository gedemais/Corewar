/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_functions3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 00:15:40 by moguy             #+#    #+#             */
/*   Updated: 2019/11/27 08:23:20 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				sti(t_env *env, t_process *p)
{
	int32_t		val[3];

	val[0] = p->instruct.args[0].arg;
	val[1] = p->instruct.args[1].arg;
	val[2] = p->instruct.args[2].arg;
	if ((p->instruct.args[2].type == T_REG && (val[2] <= REG_NONE
					|| val[2] >= REG_MAX)) || (
					p->instruct.args[1].type == T_REG && (val[1] <= REG_NONE
			|| val[1] >= REG_MAX)) || val[0] <= REG_NONE || val[0] >= REG_MAX)
		return ;
	val[0] = get_arg_value(env, p, 0, true);
	val[1] = get_arg_value(env, p, 1, true);
	val[2] = get_arg_value(env, p, 2, true);
	p->pctmp = p->pc + ((val[1] + val[2]) % IDX_MOD);
	write_mem_cell(env, p, val[0]);
}

void				op_fork(t_env *env, t_process *p)
{
	unsigned int	i;

	i = 0;
	p->pctmp = p->pc + (uint16_t)(p->instruct.args[0].arg % IDX_MOD);
	if (!(env->process = push_lst(env->process, (uint32_t)p->r[0], p->pctmp)))
	{
		error(LST_ERR, NULL, NULL);
		exit(EXIT_FAILURE);
	}
	env->process->alive = p->alive;
	env->process->carry = p->carry;
	while (i < REG_NUMBER)
	{
		env->process->r[i] = p->r[i];
		i++;
	}
}

void				lld(t_env *env, t_process *p)
{
	int32_t		value;
	int32_t		reg;

	value = get_arg_value(env, p, 0, false);
	reg = p->instruct.args[1].arg;
	if (reg <= REG_NONE || reg >= REG_MAX)
		return ;
	p->r[reg - 1] = value;
	if (value)
		p->carry = false;
	else
		p->carry = true;
}

void				lldi(t_env *env, t_process *p)
{
	int32_t		val[3];

	val[0] = p->instruct.args[0].arg;
	val[1] = p->instruct.args[1].arg;
	val[2] = p->instruct.args[2].arg;
	if ((p->instruct.args[0].type == T_REG && (val[0] <= REG_NONE
					|| val[0] >= REG_MAX)) || (
					p->instruct.args[1].type == T_REG && (val[1] <= REG_NONE
			|| val[1] >= REG_MAX)) || val[2] <= REG_NONE || val[2] >= REG_MAX)
		return ;
	val[0] = get_arg_value(env, p, 0, true);
	val[1] = get_arg_value(env, p, 1, true);
	p->pctmp = p->pc + (uint16_t)(val[0] + val[1]);
	p->r[val[2] - 1] = get_mem_cell(env, p, REG_SIZE);
}

void				lfork(t_env *env, t_process *p)
{
	unsigned int	i;

	i = 0;
	p->pctmp = p->pc + (uint16_t)p->instruct.args[0].arg;
	if (!(env->process = push_lst(env->process, (uint32_t)p->r[0], p->pctmp)))
	{
		error(LST_ERR, NULL, NULL);
		free_env(env, NULL);
		exit(EXIT_FAILURE);
	}
	env->process->alive = p->alive;
	env->process->carry = p->carry;
	while (i < REG_NUMBER)
	{
		env->process->r[i] = p->r[i];
		i++;
	}
}
