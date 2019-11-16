/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 11:16:20 by moguy             #+#    #+#             */
/*   Updated: 2019/11/08 04:08:51 by unknown          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				live(t_env *env, t_process *p)
{
	unsigned int	i;

	i = 0;
	env->live_pl[p->instruct.args[0].arg - 1]++;
	env->last_live = p->instruct.args[0].arg;
	while (i < env->nb_pl && env->player[i].id != env->last_live)
		i++;
	printf("un processus dit que le joueur %u(%s) est en vie\n",
				env->player[i].id, &env->player[i].name[0]);
	return (0);
}

int				ld(t_env *env, t_process *p)
{
	if (p->instruct.args[0].type == ARG_DIR)
		p->r[p->instruct.args[1].id - 1] = (int32_t)p->instruct.args[0].arg;
	else
	{
		p->tpc = p->pc + (p->instruct.args[0].arg % IDX_MOD);
		ft_memcpy(&p->r[p->instruct.args[1].id - 1],
			&env->arena[p->tpc], REG_SIZE);
	}
	p->carry = true;
	return (0);
}

int				st(t_env *env, t_process *p)
{
	if (p->instruct.args[1].type == ARG_IND)
	{
		p->tpc = p->pc + (p->instruct.args[1].arg % IDX_MOD);
		ft_memcpy(&env->arena[p->tpc], &p->r[p->instruct.args[0].id - 1],
			REG_SIZE);
	}
	if (p->instruct.args[1].type == ARG_REG)
		ft_memcpy(&p->r[p->instruct.args[1].id - 1],
			&p->r[p->instruct.args[0].id - 1], REG_SIZE);
	return (0);
}

int				add(t_env *env, t_process *p)
{
	int32_t	tmp;

	(void)env;
	tmp = p->r[p->instruct.args[0].id - 1] + p->r[p->instruct.args[1].id - 1];
	p->r[p->instruct.args[2].id - 1] = tmp;
	p->carry = true;
	return (0);
}

int				sub(t_env *env, t_process *p)
{
	int32_t	tmp;

	(void)env;
	tmp = p->r[p->instruct.args[0].id - 1] - p->r[p->instruct.args[1].id - 1];
	p->r[p->instruct.args[2].id - 1] = tmp;
	p->carry = true;
	return (0);
}

u_int32_t		get_direct(t_env *env, t_process *p, t_op_arg args)
{
	u_int32_t	tmp;

	if (args.type == ARG_DIR)
		return (args.arg);
	else if (args.type == ARG_IND)
	{
		ft_memcpy(&tmp, &env->arena[p->pc + args.arg], REG_SIZE);
		return (tmp);
	}
	else if (args.type == ARG_REG)
		return ((u_int32_t)p->r[args.id - 1]);
	return (0);
}

int				and(t_env *env, t_process *p)
{
	u_int32_t	tmp;
	u_int32_t	tmp2;

	tmp = get_direct(env, p, p->instruct.args[0]);
	tmp2 = get_direct(env, p, p->instruct.args[1]);
	tmp &= tmp2;
	p->r[p->instruct.args[2].id - 1] = (int32_t)tmp;
	p->carry = true;
	return (0);
}

int				xor(t_env *env, t_process *p)
{
	u_int32_t	tmp;
	u_int32_t	tmp2;

	tmp = get_direct(env, p, p->instruct.args[0]);
	tmp2 = get_direct(env, p, p->instruct.args[1]);
	tmp ^= tmp2;
	p->r[p->instruct.args[2].id - 1] = (int32_t)tmp;
	p->carry = true;
	return (0);
}

int				or(t_env *env, t_process *p)
{
	u_int32_t	tmp;
	u_int32_t	tmp2;

	tmp = get_direct(env, p, p->instruct.args[0]);
	tmp2 = get_direct(env, p, p->instruct.args[1]);
	tmp |= tmp2;
	p->r[p->instruct.args[2].id - 1] = (int32_t)tmp;
	p->carry = true;
	return (0);
}

int				zjmp(t_env *env, t_process *p)
{
	(void)env;
	if (p->carry == false)
		return (1);
	p->pc += (u_int16_t)((u_int16_t)p->instruct.args[0].arg % IDX_MOD);
	return (0);
}

int				ldi(t_env *env, t_process *p)
{
	if (p->instruct.args[0].type == ARG_IND)
	{
		p->tpc = p->pc + (p->instruct.args[0].arg % IDX_MOD);
		if (p->instruct.args[1].type == ARG_REG)
			p->tpc += p->instruct.args[1].id;
		else
			p->tpc += p->instruct.args[1].arg;
	}
	else if (p->instruct.args[0].type == ARG_REG)
	{	
		if (p->instruct.args[1].type == ARG_REG)
			p->tpc = p->instruct.args[0].id + p->instruct.args[1].id;
		else
			p->tpc = p->instruct.args[0].id + p->instruct.args[1].arg;
	}
	else if (p->instruct.args[1].type == ARG_REG)
		p->tpc = p->instruct.args[0].arg + p->instruct.args[1].id;
	else
		p->tpc = p->instruct.args[0].arg + p->instruct.args[1].arg;
	p->tpc = p->pc + (p->tpc % IDX_MOD);
	ft_memcpy(&p->r[p->instruct.args[2].id - 1], &env->arena[p->tpc], REG_SIZE);
	p->carry = true;
	return (0);
}

int				sti(t_env *env, t_process *p)
{
	p->tpc = p->instruct.args[1].arg + p->instruct.args[2].arg;
	ft_memcpy(&env->arena[p->tpc], &p->r[p->instruct.args[0].id - 1], REG_SIZE);
	return (0);
}

int				forky(t_env *env, t_process *p)
{
	(void)env;
	p->tpc = p->pc + (p->instruct.args[0].arg % IDX_MOD);
	env->process = push_lst(env->process, (u_int32_t)p->r[0], p->tpc);
	return (0);
}

int				lld(t_env *env, t_process *p)
{
	if (p->instruct.args[0].type == ARG_DIR)
		p->r[p->instruct.args[1].id - 1] = (int32_t)p->instruct.args[0].arg;
	else
	{
		p->tpc = p->pc + p->instruct.args[0].arg;
		ft_memcpy(&p->r[p->instruct.args[1].id - 1],
			&env->arena[p->tpc], REG_SIZE);
	}
	p->carry = true;
	return (0);
}

int				lldi(t_env *env, t_process *p)
{
	if (p->instruct.args[0].type == ARG_IND)
	{
		p->tpc = p->pc + p->instruct.args[0].arg;
		if (p->instruct.args[1].type == ARG_REG)
			p->tpc += p->instruct.args[1].id;
		else
			p->tpc += p->instruct.args[1].arg;
	}
	else if (p->instruct.args[0].type == ARG_REG)
	{	
		if (p->instruct.args[1].type == ARG_REG)
			p->tpc = p->instruct.args[0].id + p->instruct.args[1].id;
		else
			p->tpc = p->instruct.args[0].id + p->instruct.args[1].arg;
	}
	else if (p->instruct.args[1].type == ARG_REG)
		p->tpc = p->instruct.args[0].arg + p->instruct.args[1].id;
	else
		p->tpc = p->instruct.args[0].arg + p->instruct.args[1].arg;
	p->tpc = p->pc + p->tpc;
	ft_memcpy(&p->r[p->instruct.args[2].id - 1], &env->arena[p->tpc], REG_SIZE);
	p->carry = true;
	return (0);
}

int				lfork(t_env *env, t_process *p)
{
	(void)env;
	p->tpc = p->pc + p->instruct.args[0].arg;
	env->process = push_lst(env->process, (u_int32_t)p->r[0], p->tpc);
	return (0);
}

int				aff(t_env *env, t_process *p)
{
	(void)env;
	ft_putchar((char)(p->r[p->instruct.args[0].id - 1] % 256));
	return (0);
}
