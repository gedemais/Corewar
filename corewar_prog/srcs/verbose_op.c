/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 07:08:48 by moguy             #+#    #+#             */
/*   Updated: 2020/02/07 08:13:24 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline void	help_verbose3(t_env *env, t_process *p, uint32_t op, int i)
{
	if (i + 1 < g_func_tab[op - 1].nb_arg)
		{
			env->arg.str = " ";
			buffer_cor(env->arg, 0, 0);
		}
	else
	{
		if (op == OP_FORK || op == OP_LFORK)
		{
			env->arg.str = " (";
			buffer_cor(env->arg, 0, 0);
			if (op == OP_FORK)
				env->arg.n = p->pc + (p->instruct.args[0].arg % IDX_MOD);
			else
				env->arg.n = p->pc + p->instruct.args[0].arg;
			buffer_cor(env->arg, 3, 0);
			env->arg.str = ")";
			buffer_cor(env->arg, 0, 0);
		}
		else if (op == OP_ZJMP)
		{
			env->arg.str = (p->carry) ? " OK" : " FAILED";
			buffer_cor(env->arg, 0, 0);
		}
		env->arg.str = "\n";
		buffer_cor(env->arg, 0, 0);
	}
}

static inline void	help_verbose2(t_env *env, t_process *p, uint32_t op, int i)
{
	if (p->instruct.args[i].type == T_REG)
	{
		if (((op == OP_LLDI || op == OP_LDI || op == OP_AND || op == OP_XOR
						|| op == OP_OR) && (i == 0 || i == 1)) || (op == OP_AFF
						&& i == 0) || (op == OP_STI && (i == 1 || i == 2)))
		{
			env->arg.n = p->r[p->instruct.args[i].arg - 1];
			buffer_cor(env->arg, 3, 0);
		}
		else if (op == OP_ST && i == 1)
		{
			env->arg.n = p->instruct.args[i].arg;
			buffer_cor(env->arg, 3, 0);
		}
		else
		{
			env->arg.str = "r";
			buffer_cor(env->arg, 0, 0);
			env->arg.n = p->instruct.args[i].arg;
			buffer_cor(env->arg, 3, 0);
		}
	}
	else if (p->instruct.args[i].type == T_IND)
	{
		if (((op == OP_LD || op == OP_LDI || op == OP_LLD || op == OP_LLDI)
					&& i == 0)
				|| ((op == OP_AND || op == OP_OR || op == OP_XOR)
					&& (i == 0 || i == 1))
				|| (op == OP_STI && i == 1))
		{
			env->arg.n = get_arg_value(env, p, i, (
							op == OP_LLDI || op == OP_LLD) ? 0 : 1);
			buffer_cor(env->arg, 3, 0);
		}
		else
		{
			env->arg.n = p->instruct.args[i].arg;
			buffer_cor(env->arg, 3, 0);
		}
	}
	else
	{
			env->arg.n = p->instruct.args[i].arg;
			buffer_cor(env->arg, 3, 0);
	}
}

static inline void	help_verbose_op(t_env *env, t_process *p, uint32_t op)
{
	int				i;
	int32_t			arg;

	i = -1;
	while (++i < g_func_tab[op - 1].nb_arg)
	{
		help_verbose2(env, p, op, i);
		help_verbose3(env, p, op, i);
	}
	if (p->instruct.op == OP_LDI)
	{
		arg = (get_arg_value(env, p, 0, true) + get_arg_value(env, p, 1, true));
		env->arg.str = "       | -> load from ";
		buffer_cor(env->arg, 0, 0);
		env->arg.n = get_arg_value(env, p, 0, true);
		buffer_cor(env->arg, 3, 0);
		env->arg.str = " + ";
		buffer_cor(env->arg, 0, 0);
		env->arg.n = get_arg_value(env, p, 1, true);
		buffer_cor(env->arg, 3, 0);
		env->arg.str = " = ";
		buffer_cor(env->arg, 0, 0);
		env->arg.n = arg;
		buffer_cor(env->arg, 3, 0);
		env->arg.str = " (with pc and mod ";
		buffer_cor(env->arg, 0, 0);
		env->arg.n = p->pc + (arg % IDX_MOD);
		buffer_cor(env->arg, 3, 0);
		env->arg.str = ")\n";
		buffer_cor(env->arg, 0, 0);
	}
	else if (p->instruct.op == OP_STI)
	{
		arg = (get_arg_value(env, p, 1, true) + get_arg_value(env, p, 2, true));
		env->arg.str = "       | -> store to ";
		buffer_cor(env->arg, 0, 0);
		env->arg.n = get_arg_value(env, p, 1, true);
		buffer_cor(env->arg, 3, 0);
		env->arg.str = " + ";
		buffer_cor(env->arg, 0, 0);
		env->arg.n = get_arg_value(env, p, 2, true);
		buffer_cor(env->arg, 3, 0);
		env->arg.str = " = ";
		buffer_cor(env->arg, 0, 0);
		env->arg.n = arg;
		buffer_cor(env->arg, 3, 0);
		env->arg.str = " (with pc and mod ";
		buffer_cor(env->arg, 0, 0);
		env->arg.n = p->pc + (arg % IDX_MOD);
		buffer_cor(env->arg, 3, 0);
		env->arg.str = ")\n";
		buffer_cor(env->arg, 0, 0);
	}
}

void				verbose_op(t_env *env, t_process *p)
{
	int				i;
	uint32_t		op;

	i = p->rank;
	op = p->instruct.op;
	if (i < 10)
		env->arg.str = "P    ";
	else if (i >= 10 && i < 100)
		env->arg.str = "P   ";
	else if (i >= 100 && i < 1000)
		env->arg.str = "P  ";
	else if (i >= 1000 && i < 10000)
		env->arg.str = "P ";
	else
		env->arg.str = "P ";
	buffer_cor(env->arg, 0, 0);
	env->arg.n = i;
	buffer_cor(env->arg, 3, 0);
	env->arg.str = " | ";
	buffer_cor(env->arg, 0, 0);
	env->arg.str = g_func_tab[p->instruct.op - 1].name;
	buffer_cor(env->arg, 0, 0);
	env->arg.str = " ";
	buffer_cor(env->arg, 0, 0);
	help_verbose_op(env, p, op);
}
