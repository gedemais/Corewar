/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 07:08:48 by moguy             #+#    #+#             */
/*   Updated: 2020/02/05 07:26:14 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline void	help_verbose3(t_process *p, uint32_t op, int i)
{
	if (i + 1 < g_func_tab[op - 1].nb_arg)
		printf(" ");
	else
	{
		if (op == OP_FORK)
			printf(" (%d)", (p->pc + (p->instruct.args[0].arg % IDX_MOD)));
		else if (op == OP_LFORK)
			printf(" (%d)", (p->pc + p->instruct.args[0].arg));
		else if (op == OP_ZJMP)
			printf((p->carry) ? " OK" : " FAILED");
		printf("\n");
	}
}

static inline void	help_verbose2(t_env *env, t_process *p, uint32_t op, int i)
{
	if (p->instruct.args[i].type == T_REG)
	{
		if (((op == OP_LLDI || op == OP_LDI || op == OP_AND || op == OP_XOR
						|| op == OP_OR) && (i == 0 || i == 1)) || (op == OP_AFF
						&& i == 0) || (op == OP_STI && (i == 1 || i == 2)))
			printf("%d", p->r[p->instruct.args[i].arg - 1]);
		else if (op == OP_ST && i == 1)
			printf("%d", p->instruct.args[i].arg);
		else
			printf("r%d", p->instruct.args[i].arg);
	}
	else if (p->instruct.args[i].type == T_IND)
	{
		if (((op == OP_LD || op == OP_LDI || op == OP_LLD || op == OP_LLDI)
					&& i == 0)
				|| ((op == OP_AND || op == OP_OR || op == OP_XOR)
					&& (i == 0 || i == 1))
				|| (op == OP_STI && i == 1))
			printf("%d", get_arg_value(env, p, i, (
							op == OP_LLDI || op == OP_LLD) ? 0 : 1));
		else
			printf("%d", p->instruct.args[i].arg);
	}
	else
		printf("%d", p->instruct.args[i].arg);
}

static inline void	help_verbose_op(t_env *env, t_process *p, uint32_t op)
{
	int				i;
	int32_t			arg;

	i = -1;
	while (++i < g_func_tab[op - 1].nb_arg)
	{
		help_verbose2(env, p, op, i);
		help_verbose3(p, op, i);
	}
	if (p->instruct.op == OP_LDI)
	{
		arg = (get_arg_value(env, p, 0, true) + get_arg_value(env, p, 1, true));
		printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",\
				get_arg_value(env, p, 0, true), get_arg_value(
					env, p, 1, true), arg, p->pc + (arg % IDX_MOD));
	}
	else if (p->instruct.op == OP_STI)
	{
		arg = (get_arg_value(env, p, 1, true) + get_arg_value(env, p, 2, true));
		printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",\
		get_arg_value(env, p, 1, true), get_arg_value(
					env, p, 2, true), arg, p->pc + (arg % IDX_MOD));
	}
}

void				verbose_op(t_env *env, t_process *p)
{
	int				i;
	uint32_t		op;

	i = p->rank;
	op = p->instruct.op;
	if (i < 10000)
		printf("P%5d | %s ", i, g_func_tab[p->instruct.op - 1].name);
	else if (i >= 10000 && i < 100000)
		printf("P%6d | %s ", i, g_func_tab[p->instruct.op - 1].name);
	else if (i >= 100000 && i < 1000000)
		printf("P%7d | %s ", i, g_func_tab[p->instruct.op - 1].name);
	else if (i >= 1000000 && i < 10000000)
		printf("P%8d | %s ", i, g_func_tab[p->instruct.op - 1].name);
	else if (i >= 10000000 && i < 100000000)
		printf("P%9d | %s ", i, g_func_tab[p->instruct.op - 1].name);
	else if (i >= 100000000 && i < 1000000000)
		printf("P%10d | %s ", i, g_func_tab[p->instruct.op - 1].name);
	else if (i >= 1000000000 && i <= INT_MAX)
		printf("P%11d | %s ", i, g_func_tab[p->instruct.op - 1].name);
	help_verbose_op(env, p, op);
}
