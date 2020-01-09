/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:44:18 by moguy             #+#    #+#             */
/*   Updated: 2019/12/04 11:48:37 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int32_t			get_mem_cell(t_env *env, t_process *p, size_t siz)
{
	size_t			i;
	int32_t			val;
	uint8_t			tmp;
	bool			sign;

	i = 0;
	val = 0;
	sign = (bool)(env->arena[p->pctmp] & MASK_NEG);
	while (i < siz)
	{
		val <<= 8;
		tmp = env->arena[p->pctmp + i];
		val |= (sign) ? (tmp ^ MASK_FF) : tmp;
		i++;
	}
	(sign) ? val = ~(val) : 1;
	return (val);
}

int32_t					get_arg_value(t_env *env, t_process *p, int i, bool mod)
{
	int32_t				value;
	int32_t				arg;

	arg = p->instruct.args[i].arg;
	if (p->instruct.args[i].type == T_DIR)
		value = arg;
	else if (p->instruct.args[i].type == T_REG)
		value = p->r[arg - 1];
	else
	{
		p->pctmp = p->pc + (uint32_t)((mod) ? arg % IDX_MOD : arg);
		value = get_mem_cell(env, p, REG_SIZE);
	}
	return (value);
}

static inline void	get_args(t_env *env, t_process *p, bool dir)
{
	int				i;
	int				j;

	i = MAX_ARGS_NUMBER;
	j = 0;
	p->pctmp = p->tpc++;
	p->encoding = (uint8_t)get_mem_cell(env, p, 1);
	while (i-- > 0)
	{
		p->pctmp = p->tpc;
		p->instruct.args[j].type = (p->encoding >> (2 * i)) & MASK_ENCO;
		if (((p->encoding >> (2 * i)) & MASK_ENCO) == DIR_CODE
			&& (p->instruct.args[j].type = T_DIR)
			&& (p->tpc = p->tpc + ((dir) ? 2 : 4)))
			p->instruct.args[j].arg = get_mem_cell(env, p, (dir) ? 2 : 4);
		else if (((p->encoding >> (2 * i)) & MASK_ENCO) == IND_CODE
			&& (p->instruct.args[j].type = T_IND) && (p->tpc = p->tpc + 2))
			p->instruct.args[j].arg = get_mem_cell(env, p, 2);
		else if (((p->encoding >> (2 * i)) & MASK_ENCO) == REG_CODE
			&& (p->instruct.args[j].type = T_REG) && (p->tpc++))
			p->instruct.args[j].arg = get_mem_cell(env, p, 1);
		else
			return ;
		j++;
	}
}

bool				reg_is_valid(t_op_arg arg[MAX_ARGS_NUMBER])
{
	int				i;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		if (arg[i].type == T_REG)
			if (arg[i].arg <= REG_NONE || arg[i].arg >= REG_MAX)
				return (false);
		i++;
	}
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
	else if (p->instruct.op == OP_AFF)
	{
		p->pctmp = p->tpc + 1;
		p->tpc += 2;
		p->instruct.args[0].type = T_REG;
		p->instruct.args[0].arg = get_mem_cell(env, p, 1);
	}
	else
		get_args(env, p, dir);
//	if (env->opt[V] & (1 << 2) && reg_is_valid(p->instruct.args))
//		verbose_op(p);
}
