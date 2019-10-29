/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:44:18 by moguy             #+#    #+#             */
/*   Updated: 2019/10/29 17:16:37 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

uint32_t			get_mem_cell(t_env *env, t_process *p, size_t siz,
	uint16_t address)
{
	uint32_t		val;
	unsigned int	i;

	i = 0;
	val = 0;
	while (i < siz)
	{
		val |= (uint32_t)env->arena[(address + i) & 0xfff] << (8 * i);
		i++;
	}
	p->pc += siz;
	return (val);
}

static inline void	get_args(t_env *env, t_process *p, bool dir)
{
	int				i;
	int				j;
	uint8_t			encoding;
	uint8_t			type;

	i = MAX_ARGS_NUMBER;
	j = 0;
	encoding = env->arena[p->pc];
	p->pc += 1;
	while (i-- > 0)
	{
		type = (encoding >> (2 * i)) & MASK_ENCO;
		p->instruct.args[j].type = type;
		if (type == ARG_DIR)
			p->instruct.args[j].dir.arg = get_mem_cell(env, p,
			(dir == 0) ? 2 : 4, p->pc);
		else if (type == ARG_IND)
			p->instruct.args[j].dir.arg = get_mem_cell(env, p, 2, p->pc);
		else if (type == ARG_REG)
			if ((p->instruct.args[j].reg.id = get_mem_cell(
				env, p, 1, p->pc)) <= REG_NONE
				|| p->instruct.args[j].reg.id >= REG_MAX)
				p->instruct.op = OP_NONE;
		j++;
	}
}

void	load_args(t_env *env, t_process *p, bool enco, bool dir)
{
	if (enco == false)
	{
		p->instruct.args[0].type = ARG_DIR;
		p->instruct.args[0].dir.arg = get_mem_cell(env, p,
			(dir == 0) ? 2 : 4, p->pc);
		p->pc += (dir == 0) ? 2 : 4;
	}
	else
		get_args(env, p, dir);
	if (!is_op_arg_valid(p))
		p->instruct.op = OP_NONE;
}
