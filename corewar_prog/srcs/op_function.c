/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 11:16:20 by moguy             #+#    #+#             */
/*   Updated: 2019/10/19 17:02:54 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				live(t_env *env, t_process *pro)
{
	int		player;

	player = pro->r[0];
	env->nb_lives[player]++;
	return (0);
}
/*
int				ld(t_env *env, t_process *pro)
{
	return (0);
}

int				st(t_env *env, t_process *pro)
{
	
	return (0);
}

int				add(t_env *env, t_process *pro)
{
	return (0);
}

int				sub(t_env *env, t_process *pro)
{
	return (0);
}

int				and(t_env *env, t_process *pro)
{
	return (0);
}

int				xor(t_env *env, t_process *pro)
{
	return (0);
}

int				or(t_env *env, t_process *pro)
{
	return (0);
}

int				zjmp(t_env *env, t_process *pro)
{
	return (0);
}

int				ldi(t_env *env, t_process *pro)
{
	return (0);
}

int				sti(t_env *env, t_process *pro)
{
	return (0);
}

int				forky(t_env *env, t_process *pro)
{
	return (0);
}

int				lld(t_env *env, t_process *pro)
{
	return (0);
}

int				lldi(t_env *env, t_process *pro)
{
	return (0);
}

int				lfork(t_env *env, t_process *pro)
{
	return (0);
}

int				aff(t_env *env, t_process *pro)
{
	return (0);
}*/
