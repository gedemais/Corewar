/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 11:16:20 by moguy             #+#    #+#             */
/*   Updated: 2019/12/04 07:11:09 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				live(t_env *env, t_process *p)
{
	int32_t			value;

	env->curr_lives++;
	value = -(get_arg_value(env, p, 0, true));
	p->alive = env->cycle_tot + env->cycle_curr;
	if (value < 1 || value > (int32_t)env->nb_pl)
		return ;
	env->live_pl[value - 1]++;
	env->last_live = (uint32_t)value;
	if (!(env->opt[V] & (1 << 0)))
		return ;
	printf("Player %u (%s) is said to be alive\n",
				env->player[value - 1].id, &env->player[value - 1].name[0]);
}

void				ld(t_env *env, t_process *p)
{
	int32_t		value;
	int32_t		reg;

	value = get_arg_value(env, p, 0, true);
	reg = p->instruct.args[1].arg;
	if (reg <= REG_NONE || reg >= REG_MAX)
		return ;
	p->r[reg - 1] = value;
	if (value)
		p->carry = false;
	else
		p->carry = true;
}

void				st(t_env *env, t_process *p)
{
	int32_t		value;
	int32_t		tmp;

	if (!reg_is_valid(p->instruct.args))
		return ;
	value = get_arg_value(env, p, 0, true);
	tmp = p->instruct.args[1].arg;
	if (p->instruct.args[1].type == T_REG)
		p->r[tmp - 1] = value;
	else if (p->instruct.args[1].type == T_IND)
	{
		p->pctmp = p->pc + (tmp % IDX_MOD);
		write_mem_cell(env, p, value);
	}
}

void				add(t_env *env, t_process *p)
{
	int32_t		val[3];

	if (!reg_is_valid(p->instruct.args))
		return ;
	val[0] = get_arg_value(env, p, 0, true);
	val[1] = get_arg_value(env, p, 1, true);
	val[2] = p->instruct.args[2].arg;
	p->r[val[2] - 1] = val[0] + val[1];
	p->carry = (p->r[val[2] - 1]) ? false : true;
}

void				sub(t_env *env, t_process *p)
{
	int32_t		val[3];

	if (!reg_is_valid(p->instruct.args))
		return ;
	val[0] = get_arg_value(env, p, 0, true);
	val[1] = get_arg_value(env, p, 1, true);
	val[2] = p->instruct.args[2].arg;
	p->r[val[2] - 1] = val[0] - val[1];
	p->carry = (p->r[val[2] - 1]) ? false : true;
}
