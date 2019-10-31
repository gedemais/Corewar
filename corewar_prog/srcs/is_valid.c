/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:06:59 by moguy             #+#    #+#             */
/*   Updated: 2019/10/30 16:13:48 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

bool	is_sti_valid(t_process *p)
{
	static bool		g_valid_sti[ARG_MX][ARG_MX][ARG_MX];

	g_valid_sti[ARG_REG][ARG_DIR][ARG_DIR] = true;
	g_valid_sti[ARG_REG][ARG_IND][ARG_DIR] = true;
	g_valid_sti[ARG_REG][ARG_REG][ARG_DIR] = true;
	g_valid_sti[ARG_REG][ARG_DIR][ARG_REG] = true;
	g_valid_sti[ARG_REG][ARG_IND][ARG_REG] = true;
	g_valid_sti[ARG_REG][ARG_REG][ARG_REG] = true;
	return (g_valid_sti[p->instruct.args[0].type][p->instruct.args[1].type][
			p->instruct.args[2].type]);
}

bool	is_ldi_valid(t_process *p)
{
	static bool		g_valid_ldi[ARG_MX][ARG_MX][ARG_MX];

	g_valid_ldi[ARG_DIR][ARG_DIR][ARG_REG] = true;
	g_valid_ldi[ARG_IND][ARG_DIR][ARG_REG] = true;
	g_valid_ldi[ARG_REG][ARG_DIR][ARG_REG] = true;
	g_valid_ldi[ARG_DIR][ARG_REG][ARG_REG] = true;
	g_valid_ldi[ARG_IND][ARG_REG][ARG_REG] = true;
	g_valid_ldi[ARG_REG][ARG_REG][ARG_REG] = true;
	return (g_valid_ldi[p->instruct.args[0].type][p->instruct.args[1].type][
			p->instruct.args[2].type]);
}

bool	is_xor_valid(t_process *p)
{
	static bool		g_valid_xor[ARG_MX][ARG_MX][ARG_MX];

	g_valid_xor[ARG_DIR][ARG_DIR][ARG_REG] = true;
	g_valid_xor[ARG_IND][ARG_DIR][ARG_REG] = true;
	g_valid_xor[ARG_REG][ARG_DIR][ARG_REG] = true;
	g_valid_xor[ARG_DIR][ARG_IND][ARG_REG] = true;
	g_valid_xor[ARG_IND][ARG_IND][ARG_REG] = true;
	g_valid_xor[ARG_REG][ARG_IND][ARG_REG] = true;
	g_valid_xor[ARG_DIR][ARG_REG][ARG_REG] = true;
	g_valid_xor[ARG_IND][ARG_REG][ARG_REG] = true;
	g_valid_xor[ARG_REG][ARG_REG][ARG_REG] = true;
	return (g_valid_xor[p->instruct.args[0].type][p->instruct.args[1].type][
			p->instruct.args[2].type]);
}

bool	is_or_valid(t_process *p)
{
	static bool		g_valid_or[ARG_MX][ARG_MX][ARG_MX];

	g_valid_or[ARG_DIR][ARG_DIR][ARG_REG] = true;
	g_valid_or[ARG_IND][ARG_DIR][ARG_REG] = true;
	g_valid_or[ARG_REG][ARG_DIR][ARG_REG] = true;
	g_valid_or[ARG_DIR][ARG_IND][ARG_REG] = true;
	g_valid_or[ARG_IND][ARG_IND][ARG_REG] = true;
	g_valid_or[ARG_REG][ARG_IND][ARG_REG] = true;
	g_valid_or[ARG_DIR][ARG_REG][ARG_REG] = true;
	g_valid_or[ARG_IND][ARG_REG][ARG_REG] = true;
	g_valid_or[ARG_REG][ARG_REG][ARG_REG] = true;
	return (g_valid_or[p->instruct.args[0].type][p->instruct.args[1].type][
			p->instruct.args[2].type]);
}

bool	is_and_valid(t_process *p)
{
	static bool		g_valid_and[ARG_MX][ARG_MX][ARG_MX];

	g_valid_and[ARG_DIR][ARG_DIR][ARG_REG] = true;
	g_valid_and[ARG_IND][ARG_DIR][ARG_REG] = true;
	g_valid_and[ARG_REG][ARG_DIR][ARG_REG] = true;
	g_valid_and[ARG_DIR][ARG_IND][ARG_REG] = true;
	g_valid_and[ARG_IND][ARG_IND][ARG_REG] = true;
	g_valid_and[ARG_REG][ARG_IND][ARG_REG] = true;
	g_valid_and[ARG_DIR][ARG_REG][ARG_REG] = true;
	g_valid_and[ARG_IND][ARG_REG][ARG_REG] = true;
	g_valid_and[ARG_REG][ARG_REG][ARG_REG] = true;
	return (g_valid_and[p->instruct.args[0].type][p->instruct.args[1].type][
			p->instruct.args[2].type]);
}

bool	is_op_arg_valid(t_process *p, uint32_t op)
{
	if (op == OP_ZJMP || op == OP_FORK || op == OP_LFORK || op == OP_AFF)
		return (is_op_other2_valid(p));
	if (op == OP_LIVE || op == OP_ADD || op == OP_SUB)
		return (is_op_other_valid(p));
	if (op == OP_LLD || op == OP_LD || op == OP_ST)
		return (is_l_ld_st_valid(p));
	if (op == OP_LLDI)
		return (is_lldi_valid(p));
	if (op == OP_STI)
		return (is_sti_valid(p));
	if (op == OP_LDI)
		return (is_ldi_valid(p));
	if (op == OP_XOR)
		return (is_xor_valid(p));
	if (op == OP_OR)
		return (is_or_valid(p));
	if (op == OP_AND)
		return (is_and_valid(p));
	return (false);
}
