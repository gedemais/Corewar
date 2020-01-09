/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_launch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:48:03 by moguy             #+#    #+#             */
/*   Updated: 2019/12/04 12:52:06 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
			printf(" \n");
		p->pctmp++;
	}
}

static inline void	verbose_op(t_process *p)
{
	int				i;
	int32_t			arg;

	i = p->rank;
	printf("P %5d | %s ", p->rank, func_tab[p->instruct.op - 1].name);
	i = -1;
	while (++i < func_tab[p->instruct.op - 1].nb_arg)
	{
		if (p->instruct.args[i].type == T_REG)
			printf("r%d", p->instruct.args[i].arg);
		else
			printf("%d", p->instruct.args[i].arg);
		if (i + 1 < func_tab[p->instruct.op - 1].nb_arg)
			printf(" ");
		else
		{
			if (p->instruct.op == OP_FORK)
				printf(" (%d)", (p->pc + (p->instruct.args[0].arg % IDX_MOD)));
			if (p->instruct.op == OP_ZJMP)
				printf((p->carry) ? " OK" : " KO");
			printf("\n");
		}
	}
	if (p->instruct.op == OP_STI
			&& (arg = p->instruct.args[1].arg + p->instruct.args[2].arg))
		printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
				p->instruct.args[1].arg, p->instruct.args[2].arg, arg,
				p->pc + (arg % IDX_MOD));
}

void				launch_instruct(t_env *env, t_process *p)
{
	bool			enco;

	if (p->instruct.op <= OP_NONE || p->instruct.op >= OP_MAX)
		return ;
	enco = (bool)func_tab[p->instruct.op - 1].encoding;
	load_args(env, p, enco, (bool)func_tab[p->instruct.op - 1].direct);
	if (env->opt[V] & (1 << 2) && reg_is_valid(p->instruct.args)
			&& p->encoding > ((enco) ? 0 : -1))
		verbose_op(p);
	func_tab[p->instruct.op - 1].f(env, p);
	if (env->opt[V] & (1 << 4) && p->instruct.op != OP_ZJMP)
		verbose_pc(env, p);
}

void				create_instruct(t_env *env, t_process *p)
{
	p->pc = p->tpc;
	p->pctmp = p->pc;
	p->tpc++;
	p->instruct.op = (uint32_t)get_mem_cell(env, p, 1);
	if (p->instruct.op <= OP_NONE || p->instruct.op >= OP_MAX)
		p->cycle_to_exec = 0;
	else
		p->cycle_to_exec = (int)func_tab[p->instruct.op - 1].wait_cycles;
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
