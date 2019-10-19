/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:09:46 by moguy             #+#    #+#             */
/*   Updated: 2019/10/19 17:22:46 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline void	get_encoding_byte(t_instruct *inst, char enco, bool s_i)
{
	(void)inst;
	(void)enco;
	(void)s_i;
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
		process->instruct.type[0] = 1;
		process->instruct.arg[0].direct4 = hex_conv4(env->arena[process->pci],
				env->arena[process->pci + 1], env->arena[process->pci + 2],
				env->arena[process->pci + 3]);
	}
	else
	{
		inst->type[0] = 0;
		process->instruct.arg[0].direct2 = hex_conv2(env->arena[process->pci],
				env->arena[process->pci + 1]);
	}
	process->pci = (s_i) ? process->pci + 4 : process->pci + 2;
}

int					load_op(t_env *env, t_process *process)
{
	process->pci = process->pc + 1;
	if (encoding_byte(process->instruct.op_code))
	{
		if ((get_args(env, process,
						direct_size(process->instruct.op_code))) == 0)
			return (1);
	}
	else
		if ((get_arg(env, process,
						direct_size(process->instruct.op_code))) == 0)
			return (1);
	process->carry = carry_flag(process->instruct.op_code);
	return (0);
}
