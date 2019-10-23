/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:09:46 by moguy             #+#    #+#             */
/*   Updated: 2019/10/23 21:16:54 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

static inline void	get_encoding_byte(t_process *pro, char enco, bool s_i)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		pro->instruct.type[i] = (enco >> (2 * (i + 1))) & MASK_ENCO;
		if (pro->instruct.type[i] == 2 && s_i == 1)
			pro->instruct.type[i] = 0;
		i++;
	}
}

static inline void	get_args(t_env *env, t_process *process, bool s_i)
{
	get_encoding_byte(process, env->arena[process->pci], s_i);
	process->pci++;
	check_type(env, process);
	process->pci++;
}

static inline void	get_arg(t_env *env, t_process *process, bool s_i)
{
	if (s_i)
	{
		process->instruct.type[0] = 2;
		process->instruct.arg[0].direct4 = hex_conv4(env->arena[process->pci],
				env->arena[process->pci + 1], env->arena[process->pci + 2],
				env->arena[process->pci + 3]);
	}
	else
	{
		process->instruct.type[0] = 0;
		process->instruct.arg[0].direct2 = hex_conv2(env->arena[process->pci],
				env->arena[process->pci + 1]);
	}
	process->pci = (s_i == true) ? process->pci + 4 : process->pci + 2;
}

int					load_op(t_env *env, t_process *process)
{
	process->pci = process->pc + 1;
	if (encoding_byte(process->instruct.op_code))
		get_args(env, process, direct_size(process->instruct.op_code));
	else
		get_arg(env, process, direct_size(process->instruct.op_code));
	process->carry = carry_flag(process->instruct.op_code);
	process->pc = process->pci;
	return (0);
}
