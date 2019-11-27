/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:44:18 by moguy             #+#    #+#             */
/*   Updated: 2019/11/27 08:44:34 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int32_t			get_mem_cell(t_env *env, t_process *p, size_t siz)
{
	size_t			i;
	int32_t			val;
	int32_t			tmp;
	bool			sign;

	i = 0;
	val = 0;
	sign = (bool)(env->arena[p->pctmp] & 0x80);
	while (i < siz)
	{
		val <<= 8;
		tmp = (int32_t)env->arena[p->pctmp + i];
		val |= (sign) ? tmp ^ 0xFF : tmp;
		i++;
	}
	if (sign)
		val = ~(val);
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
		p->pctmp = p->pc + (uint16_t)((mod) ? arg % IDX_MOD : arg);
		value = get_mem_cell(env, p, REG_SIZE);
	}
	return (value);
}

static inline void	get_args(t_env *env, t_process *p, bool dir)
{
	int				i;
	int				j;
	int8_t			encoding;

	i = MAX_ARGS_NUMBER;
	j = 0;
	p->pctmp = p->tpc;
	p->tpc++;
	encoding = (int8_t)get_mem_cell(env, p, 1);
	while (i-- > 0)
	{
		p->pctmp = p->tpc;
		p->instruct.args[j].type = (encoding >> (2 * i)) & MASK_ENCO;
		if (((encoding >> (2 * i)) & MASK_ENCO) == DIR_CODE
			&& (p->instruct.args[j].type = T_DIR) && (p->tpc += (dir) ? 2 : 4))
			p->instruct.args[j].arg = get_mem_cell(env, p, (dir) ? 2 : 4);
		else if (((encoding >> (2 * i)) & MASK_ENCO) == IND_CODE
			&& (p->instruct.args[j].type = T_IND) && (p->tpc += 2))
			p->instruct.args[j].arg = get_mem_cell(env, p, 2);
		else if (((encoding >> (2 * i)) & MASK_ENCO) == REG_CODE
			&& (p->instruct.args[j].type = T_REG) && (p->tpc++))
			p->instruct.args[j].arg = get_mem_cell(env, p, 1);
		else
			return ;
		j++;
	}
}
/*
static inline bool	is_op_arg_valid(t_process *p, unsigned char nb_arg)
{
	unsigned char	i;

	i = 0;
	while (i < nb_arg)
	{
		ft_putstr("\ntype = ");
		ft_putnbr((int)p->instruct.args[i].type);
		ft_putendl("");
		if (p->instruct.args[i].type != func_tab[p->instruct.op - 1].args[i])
			return (true);
		i++;
	}
	return (false);
}
*/
void				load_args(t_env *env, t_process *p, bool enco, bool dir)
{
	if (enco == false)
	{
		p->pctmp = p->tpc;
		p->tpc += (dir) ? 2 : 4;
		p->instruct.args[0].type = T_DIR;
		p->instruct.args[0].arg = get_mem_cell(env, p, (dir) ? 2 : DIR_SIZE);
	}
	else
		get_args(env, p, dir);
//	if (is_op_arg_valid(p, func_tab[p->instruct.op - 1].nb_arg))
//		p->instruct.op = OP_NONE;
}
