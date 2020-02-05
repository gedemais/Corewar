/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:44:18 by moguy             #+#    #+#             */
/*   Updated: 2020/02/05 06:06:45 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int32_t				get_mem_cell(t_env *env, t_process *p, size_t siz)
{
	size_t	i;
	int32_t	val;
	uint8_t	tmp;
	bool	sign;

	i = 0;
	val = 0;
	sign = (bool)(env->arena[p->pctmp] & MASK_NEG);
	while (i < siz)
	{
		val <<= 8;
		tmp = env->arena[p->pctmp];
		val |= (sign) ? (tmp ^ MASK_FF) : tmp;
		p->pctmp += 1;
		i++;
	}
	if (sign)
		val = ~(val);
	return (val);
}

int32_t				get_arg_value(t_env *env, t_process *p, int i, bool mod)
{
	int32_t	value;
	int32_t	arg;

	arg = p->instruct.args[i].arg;
	if (p->instruct.args[i].type == T_DIR)
		value = arg;
	else if (p->instruct.args[i].type == T_REG)
		value = p->r[arg - 1];
	else
	{
		p->pctmp = p->pc + (uint32_t)((mod) ? (arg % IDX_MOD) : arg);
		value = get_mem_cell(env, p, REG_SIZE);
	}
	return (value);
}

static inline void	get_args(t_env *env, t_process *p, bool dir)
{
	int		i;

	i = 0;
	p->tpc++;
	while (i < g_func_tab[p->instruct.op - 1].nb_arg)
	{
		p->pctmp = p->tpc;
		if ((p->instruct.args[i].type == T_DIR)
				&& (p->tpc = p->tpc + ((dir) ? 2 : 4)))
			p->instruct.args[i].arg = get_mem_cell(env, p, (dir) ? 2 : 4);
		else if ((p->instruct.args[i].type == T_IND) && (p->tpc = p->tpc + 2))
			p->instruct.args[i].arg = get_mem_cell(env, p, 2);
		else if (p->instruct.args[i].type == T_REG)
		{
			p->tpc += 1;
			p->instruct.args[i].arg = get_mem_cell(env, p, 1);
		}
		i++;
	}
}

bool				reg_is_valid(t_process *p, t_op_arg arg[MAX_ARGS_NUMBER])
{
	int		i;

	i = -1;
	while (++i < MAX_ARGS_NUMBER)
		if ((i < g_func_tab[p->instruct.op - 1].nb_arg && arg[i].type == 0)
			|| (arg[i].type == T_REG
				&& (arg[i].arg <= REG_NONE || arg[i].arg >= REG_MAX)))
			return (false);
	if ((p->instruct.op == OP_ST || p->instruct.op == OP_AFF
			|| p->instruct.op == OP_STI) && arg[0].type != T_REG)
		return (false);
	if ((p->instruct.op == OP_LD || p->instruct.op == OP_LLD)
		&& arg[1].type != T_REG)
		return (false);
	if ((p->instruct.op == OP_AND || p->instruct.op == OP_OR
			|| p->instruct.op == OP_XOR || p->instruct.op == OP_LDI
			|| p->instruct.op == OP_LLDI) && arg[2].type != T_REG)
		return (false);
	if ((p->instruct.op == OP_ADD || p->instruct.op == OP_SUB)
			&& (arg[0].type != T_REG || arg[1].type != T_REG
				|| arg[2].type != T_REG))
		return (false);
	return (true);
}

void				load_args(t_env *env, t_process *p, bool enco, bool dir)
{
	if (enco == false)
	{
		p->pctmp = p->tpc;
		p->tpc += (dir) ? 2 : 4;
		p->instruct.args[0].type = T_DIR;
		p->instruct.args[0].arg = get_mem_cell(env, p, (dir) ? 2 : 4);
	}
	else
		get_args(env, p, dir);
}
