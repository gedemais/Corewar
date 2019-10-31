/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 11:16:20 by moguy             #+#    #+#             */
/*   Updated: 2019/10/31 19:11:50 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				live(t_env *env, t_process *p)
{
	unsigned int	i;

	if (p->instruct.args[0].arg > env->nb_pl || p->instruct.args[0].arg < 1)
	{
		p->carry = 0;
		return (1);
	}
	i = 0;
	p->carry = carry_flag(p->instruct.op); 
	env->live_pl[p->instruct.args[0].arg]++;
	env->last_live = p->instruct.args[0].arg;
	while (i < env->nb_pl || env->player[i].id == env->last_live)
		i++;
	printf("un processus dit que le joueur %u(%s) est en vie",
				env->player[i].id, &env->player[i].name[0]);
	return (0);
}
/*
int				ld(t_env *env, t_process *p)
{
	return (0);
}

int				st(t_env *env, t_process *p)
{
	
	return (0);
}

int				add(t_env *env, t_process *p)
{
	return (0);
}

int				sub(t_env *env, t_process *p)
{
	return (0);
}

int				and(t_env *env, t_process *p)
{
	return (0);
}

int				xor(t_env *env, t_process *p)
{
	return (0);
}

int				or(t_env *env, t_process *p)
{
	return (0);
}

int				zjmp(t_env *env, t_process *p)
{
	return (0);
}

int				ldi(t_env *env, t_process *p)
{
	return (0);
}

int				sti(t_env *env, t_process *p)
{
	return (0);
}

int				forky(t_env *env, t_process *p)
{
	return (0);
}

int				lld(t_env *env, t_process *p)
{
	return (0);
}

int				lldi(t_env *env, t_process *p)
{
	return (0);
}

int				lfork(t_env *env, t_process *p)
{
	return (0);
}

int				aff(t_env *env, t_process *p)
{
	return (0);
}*/
