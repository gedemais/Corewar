/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 11:16:20 by moguy             #+#    #+#             */
/*   Updated: 2019/10/18 16:27:16 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				live(t_env *env, t_instruct *inst)
{
	int		player;

	player = inst->process->r[0];
	env->nb_lives[player]++;
	return (0);
}

int				ld(t_env *env, t_instruct *inst)
{
	(void)env;
	if (inst->type[0] == TYPE_DIR4)
		inst->process->r[inst->arg[1].registre] = inst->arg[0].direct;
	else if (inst->type[0] == TYPE_IND)
		inst->process->r[inst->arg[1].registre] = inst->arg[0].indirect;
	return (0);
}

int				st(t_env *env, t_instruct *inst)
{
	
	return (0);
}
/*
int				add(t_env *env, t_instruct *inst)
{
	return (0);
}

int				sub(t_env *env, t_instruct *inst)
{
	return (0);
}

int				and(t_env *env, t_instruct *inst)
{
	return (0);
}

int				xor(t_env *env, t_instruct *inst)
{
	return (0);
}

int				or(t_env *env, t_instruct *inst)
{
	return (0);
}

int				zjmp(t_env *env, t_instruct *inst)
{
	return (0);
}

int				ldi(t_env *env, t_instruct *inst)
{
	return (0);
}

int				sti(t_env *env, t_instruct *inst)
{
	return (0);
}

int				forky(t_env *env, t_instruct *inst)
{
	return (0);
}

int				lld(t_env *env, t_instruct *inst)
{
	return (0);
}

int				lldi(t_env *env, t_instruct *inst)
{
	return (0);
}

int				lfork(t_env *env, t_instruct *inst)
{
	return (0);
}

int				aff(t_env *env, t_instruct *inst)
{
	return (0);
}*/
