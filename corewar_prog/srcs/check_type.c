/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 23:34:49 by moguy             #+#    #+#             */
/*   Updated: 2019/10/19 16:38:31 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline uint16_t	registre(t_env *env, t_process *pro, int i)
{
	pro-.instruct.arg[i].registre = (int)env->arena[pro->pci];
	return (1);
}

static inline uint16_t	indirect(t_env *env, t_process *pro, int i)
{
	pro->instruct.arg[i].indirect = hex_conv2(env->arena[pro->pci],
			env->arena[pro->pci + 1]);
	return (2);
}

static inline uint16_t	direct2(t_env *env, t_process *pro, int i)
{
	pro->instruct.arg[i].direct2 = hex_conv2(env->arena[pro->pci],
			env->arena[pro->pci + 1]);
	return (2);
}

static inline uint16_t	direct4(t_env *env, t_process *pro, int i)
{
	pro->instruct.arg[i].direct4 = hex_conv4(env->arena[pro->pci],
			env->arena[pro->pci + 1], env->arena[pro->pci + 2],
			env->arena[pro->pci + 3]);
	return (4);
}

void					check_type(t_env *env, t_process *pro)
{
	static uint16_t		(*ck_type[4])(t_env*, t_process*, int) = {&direct4,
		&direct2, &indirect, &registre};
	int				i;

	i = 0;
	while (pro->instruct.type[i])
	{
		pro->pci += ck_type[pro->instruct.type[i] - '0'](env, pro, i);
		i++;
	}
}
