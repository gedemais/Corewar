/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_functions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 00:13:40 by moguy             #+#    #+#             */
/*   Updated: 2019/12/04 07:07:12 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		write_mem_cell(t_env *env, t_process *p, int32_t value)
{
	int			i;
	uint8_t		val;

	i = 0;
	while (i < REG_SIZE)
	{
		val = (uint8_t)((value << (8 * i)) >> (8 * (sizeof(int) - 1)));
		env->arena[p->pctmp] = val;
		p->pctmp++;
		i++;
	}
}

void		and(t_env *env, t_process *p)
{
	int32_t		val[3];

	if (!reg_is_valid(p->instruct.args))
		return ;
	val[0] = get_arg_value(env, p, 0, true);
	val[1] = get_arg_value(env, p, 1, true);
	val[2] = p->instruct.args[2].arg;
	p->r[val[2] - 1] = val[0] & val[1];
	p->carry = (p->r[val[2] - 1]) ? false : true;
}

void		xor(t_env *env, t_process *p)
{
	int32_t		val[3];

	if (!reg_is_valid(p->instruct.args))
		return ;
	val[0] = get_arg_value(env, p, 0, true);
	val[1] = get_arg_value(env, p, 1, true);
	val[2] = p->instruct.args[2].arg;
	p->r[val[2] - 1] = val[0] | val[1];
	p->carry = (p->r[val[2] - 1]) ? false : true;
}

void		or(t_env *env, t_process *p)
{
	int32_t		val[3];

	if (!reg_is_valid(p->instruct.args))
		return ;
	val[0] = get_arg_value(env, p, 0, true);
	val[1] = get_arg_value(env, p, 1, true);
	val[2] = p->instruct.args[2].arg;
	p->r[val[2] - 1] = val[0] ^ val[1];
	p->carry = (p->r[val[2] - 1]) ? false : true;
}

void		zjmp(t_env *env, t_process *p)
{
	int16_t		value;

	value = (int16_t)get_arg_value(env, p, 0, true);
	if (p->carry)
		p->tpc = p->pc + (value % IDX_MOD);
}
