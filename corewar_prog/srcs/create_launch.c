/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_launch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:48:03 by moguy             #+#    #+#             */
/*   Updated: 2020/02/07 06:09:13 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline void	verbose_pc(t_env *env, t_process *p)
{
	int				i;

	i = -1;
	env->arg.str = "ADV ";
	buffer_cor(env->arg, 0, 0);
	env->arg.n = p->tpc - p->pc + ((p->tpc > p->pc) ? 0 : 4096);
	buffer_cor(env->arg, 3, 0);
	env->arg.str = " (";
	buffer_cor(env->arg, 0, 0);
	env->arg.x = p->pc;
	buffer_cor(env->arg, 1, 0);
	env->arg.str = " -> ";
	buffer_cor(env->arg, 0, 0);
	env->arg.x = (p->tpc < p->pc) ? (4096 + p->tpc) : p->tpc;
	buffer_cor(env->arg, 1, 0);
	env->arg.str = ") ";
	buffer_cor(env->arg, 0, 0);
	p->pctmp = p->pc;
	while (++i < p->tpc - p->pc + ((p->tpc > p->pc) ? 0 : 4096))
	{
		env->arg.c = hex_tab((env->arena[p->pctmp] >> 4) & 0xf);
		buffer_cor(env->arg, 4, 0);
		env->arg.c = hex_tab(env->arena[p->pctmp] & 0xf);
		buffer_cor(env->arg, 4, 0);
		if (i + 1 < p->tpc - p->pc + ((p->tpc > p->pc) ? 0 : 4096))
		{
			env->arg.str = " ";
			buffer_cor(env->arg, 0, 0);
		}
		else
		{
			env->arg.str = " \n";
			buffer_cor(env->arg, 0, 0);
		}
		p->pctmp++;
	}
}

static inline int	check_encoding(t_env *env, t_process *p)
{
	int				i;
	int				j;
	uint8_t			enco;

	i = MAX_ARGS_NUMBER;
	j = 0;
	p->pctmp = p->tpc;
	p->encoding = (uint8_t)get_mem_cell(env, p, 1);
	while (i-- > 0)
	{
		enco = ((p->encoding >> (2 * i)) & MASK_ENCO);
		if (enco == DIR_CODE)
			p->instruct.args[j].type = T_DIR;
		else if (enco == IND_CODE)
			p->instruct.args[j].type = T_IND;
		else if (enco == REG_CODE)
			p->instruct.args[j].type = T_REG;
		j++;
	}
	return (0);
}

void				launch_instruct(t_env *env, t_process *p)
{
	bool			enco;

	if (p->instruct.op <= OP_NONE || p->instruct.op >= OP_MAX)
		return ;
	if (g_func_tab[p->instruct.op - 1].encoding)
	{
		if (check_encoding(env, p))
		{
			p->instruct.op = OP_NONE;
			return ;
		}
	}
	enco = (bool)g_func_tab[p->instruct.op - 1].encoding;
	load_args(env, p, enco, (bool)g_func_tab[p->instruct.op - 1].direct);
	if (reg_is_valid(p, p->instruct.args))
	{
		if (env->opt[O_V] & (1 << 2))
			verbose_op(env, p);
		g_func_tab[p->instruct.op - 1].f(env, p);
	}
	if (env->opt[O_V] & (1 << 4) && !(p->instruct.op == OP_ZJMP && p->carry))
		verbose_pc(env, p);
}

void				create_instruct(t_env *env, t_process *p)
{
	p->pc = p->tpc;
	p->pctmp = p->pc;
	p->tpc++;
	p->instruct.op = (uint32_t)get_mem_cell(env, p, 1);
	if (p->instruct.op <= OP_NONE || p->instruct.op >= OP_MAX)
		return ;
	p->cycle_to_exec = (int)g_func_tab[p->instruct.op - 1].wait_cycles;
}

int					create_pro(t_env *env, unsigned int i, unsigned int ofset)
{
	if (env->process)
	{
		if (!(env->process = push_lst(env, env->player[i].id, (uint32_t)ofset)))
			return (error(LST_ERR, NULL, NULL));
	}
	if (!env->process)
	{
		if (!(env->process = new_lst(env->player[i].id, (uint32_t)ofset)))
			return (error(LST_ERR, NULL, NULL));
		env->process->rank = 1;
	}
	env->process->tpc = env->process->pc;
	create_instruct(env, env->process);
	return (0);
}
