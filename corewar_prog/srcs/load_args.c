/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:44:18 by moguy             #+#    #+#             */
/*   Updated: 2019/11/30 08:40:08 by moguy            ###   ########.fr       */
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
	int8_t			encoding;

	i = MAX_ARGS_NUMBER;
	j = 0;
	p->pctmp = p->tpc++;
	encoding = (int8_t)get_mem_cell(env, p, 1);
	while (i-- > 0)
	{
		p->pctmp = p->tpc;
		p->instruct.args[j].type = (encoding >> (2 * i)) & MASK_ENCO;
		if (((encoding >> (2 * i)) & MASK_ENCO) == DIR_CODE
			&& (p->instruct.args[j].type = T_DIR)
			&& (p->tpc = p->tpc + ((dir) ? 2 : 4)))
			p->instruct.args[j].arg = get_mem_cell(env, p, (dir) ? 2 : 4);
		else if (((encoding >> (2 * i)) & MASK_ENCO) == IND_CODE
			&& (p->instruct.args[j].type = T_IND) && (p->tpc = p->tpc + 2))
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

static inline void	verbose_op(t_process *p)
{
	int				i;

	i = -1;
	printf("P\t%d | %s ", p->rank, func_tab[p->instruct.op - 1].name);
	while (++i < func_tab[p->instruct.op - 1].nb_arg)
	{
		if (p->instruct.args[i].type == T_REG)
			printf("r%d", p->instruct.args[i].arg);
		else
			printf("%d", p->instruct.args[i].arg);
		if (i + 1 < func_tab[p->instruct.op - 1].nb_arg)
			printf(" ");
		else
			printf("\n");
	}
}

static inline void	verbose_pc(t_env *env, t_process *p)
{
	int				i;

	i = -1;
	if (p->pc == 0)
	printf("ADV %d (0x0000 -> %#.4x) ",
			p->tpc - p->pc + ((p->tpc > p->pc) ? 0 : 4096), p->tpc);
	else
		printf("ADV %d (%#.4x -> %#.4x) ",
				p->tpc - p->pc + ((p->tpc > p->pc) ? 0 : 4096), p->pc, p->tpc);
	p->pctmp = p->pc;
	while (++i < p->tpc - p->pc + ((p->tpc > p->pc) ? 0 : 4096))
	{
		printf("%c%c", hex_tab((env->arena[p->pctmp] >> 4) & 0xf),
				hex_tab(env->arena[p->pctmp] & 0xf));
		if (i + 1 < p->tpc - p->pc + ((p->tpc > p->pc) ? 0 : 4096))
			printf(" ");
		else
			printf("\n");
		p->pctmp++;
	}
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
	if (env->opt[V] & (1 << 2))
		verbose_op(p);
	if (env->opt[V] & (1 << 4))
		verbose_pc(env, p);
//	if (is_op_arg_valid(p, func_tab[p->instruct.op - 1].nb_arg))
//		p->instruct.op = OP_NONE;
}
