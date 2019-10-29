/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:08:18 by moguy             #+#    #+#             */
/*   Updated: 2019/10/29 17:28:47 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

bool	carry_flag(uint32_t c)
{
	static bool		carry_tab[NB_FUNC] = {0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0,
									1, 1, 0, 0};

	if (c <= OP_NONE || c >= OP_MAX)
		return (0);
	return (carry_tab[c - 1]);
}

bool	direct_size(uint32_t c)
{
	static bool		direct_size[NB_FUNC] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
									0, 1, 1, 0};

	if (c <= OP_NONE || c >= OP_MAX)
		return (0);
	return (direct_size[c - 1]);
}

bool	encod_byte(uint32_t c)
{
	static bool		encoding_tab[NB_FUNC] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0,
									1, 1, 0, 1};

	if (c <= OP_NONE || c >= OP_MAX)
		return (0);
	return (encoding_tab[c - 1]);
}

bool	is_op_arg_valid(t_process *p)
{
	static bool		g_valid_op[OP_MAX][ARG_MAX][ARG_MAX][ARG_MAX] = {
		[OP_LIVE][ARG_DIR][ARG_NONE][ARG_NONE] = true,
		[OP_LD][ARG_IDIR][ARG_REG][ARG_NONE] = true,
		[OP_ST][ARG_REG][ARG_IREG][ARG_NONE] = true,
		[OP_ADD][ARG_REG][ARG_REG][ARG_REG] = true,
		[OP_SUB][ARG_REG][ARG_REG][ARG_REG] = true,
		[OP_AND][ARG_ANY][ARG_ANY][ARG_REG] = true,
		[OP_OR][ARG_ANY][ARG_ANY][ARG_REG] = true,
		[OP_XOR][ARG_ANY][ARG_ANY][ARG_REG] = true,
		[OP_ZJMP][ARG_DIR][ARG_NONE][ARG_NONE] = true,
		[OP_LDI][ARG_ANY][ARG_DREG][ARG_REG] = true,
		[OP_STI][ARG_REG][ARG_ANY][ARG_DREG] = true,
		[OP_FORK][ARG_DIR][ARG_NONE][ARG_NONE] = true,
		[OP_LLD][ARG_IDIR][ARG_REG][ARG_NONE] = true,
		[OP_LLDI][ARG_ANY][ARG_DREG][ARG_REG] = true,
		[OP_LFORK][ARG_DIR][ARG_NONE][ARG_NONE] = true,
		[OP_AFF][ARG_REG][ARG_NONE][ARG_NONE] = true
	};

	return (g_valid_op[p->instruct.op][p->instruct.args[0].type][
		p->instruct.args[1].type][p->instruct.args[2].type]);
}
