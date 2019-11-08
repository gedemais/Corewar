/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:44:18 by moguy             #+#    #+#             */
/*   Updated: 2019/11/08 03:47:09 by unknown          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

u_int32_t			get_mem_cell(t_env *env, t_process *p, size_t siz,
	u_int16_t address)
{
	u_int32_t		val;

	val = 0;
	if (siz > 2)
	{
		val |= (u_int32_t)env->arena[address] << 24;
		val |= (u_int32_t)env->arena[address + 1] << 16;
		val |= (u_int32_t)env->arena[address + 2] << 8;
		val |= (u_int32_t)env->arena[address + 3];
	}
	else if (siz > 1)
	{
		val |= (u_int32_t)env->arena[address] << 8;
		val |= (u_int32_t)env->arena[address + 1];
	}
	else
		val |= (u_int32_t)env->arena[address];
	p->pc += siz;
	return (val);
}

static inline void	get_args(t_env *env, t_process *p, bool dir)
{
	int				i;
	int				j;
	u_int8_t			encoding;

	i = MAX_ARGS_NUMBER;
	j = 0;
	encoding = (u_int8_t)get_mem_cell(env, p, 1, p->pc);
	while (i-- > 0)
	{
		p->instruct.args[j].type = (encoding >> (2 * i)) & MASK_ENCO;
		if (p->instruct.args[j].type == ARG_DIR)
		{
			p->instruct.args[j].arg = get_mem_cell(env, p,
				(dir == false) ? 4 : 2, p->pc);
		}
		else if (p->instruct.args[j].type == ARG_IND)
			p->instruct.args[j].arg = get_mem_cell(env, p, 2, p->pc);
		else if (p->instruct.args[j].type == ARG_REG)
			if ((p->instruct.args[j].id = get_mem_cell(
							env, p, 1, p->pc)) <= REG_NONE
					|| p->instruct.args[j].id >= REG_MAX)
				p->instruct.op = OP_NONE;
		j++;
	}
}

void	load_args(t_env *env, t_process *p, bool enco, bool dir)
{
	if (p->instruct.op <= OP_NONE || p->instruct.op >= OP_MAX)
		return ;
	if (enco == false)
	{
		p->instruct.args[0].type = ARG_DIR;
		p->instruct.args[0].arg = get_mem_cell(env, p,
				(dir == false) ? 4 : 2, p->pc);
	}
	else
		get_args(env, p, dir);
	if (!is_op_arg_valid(p, p->instruct.op))
	{
		p->cycle_to_exec = 0;
		p->instruct.op = OP_NONE;
	}
}
