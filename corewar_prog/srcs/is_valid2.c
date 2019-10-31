/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:38:16 by moguy             #+#    #+#             */
/*   Updated: 2019/10/30 16:13:46 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

bool	is_op_other2_valid(t_process *p)
{
	if (p->instruct.op == OP_ZJMP)
		if (p->instruct.args[0].type == ARG_DIR
				&& p->instruct.args[1].type == ARG_NONE
				&& p->instruct.args[2].type == ARG_NONE)
			return (true);
	if (p->instruct.op == OP_FORK)
		if (p->instruct.args[0].type == ARG_DIR
				&& p->instruct.args[1].type == ARG_NONE
				&& p->instruct.args[2].type == ARG_NONE)
			return (true);
	if (p->instruct.op == OP_LFORK)
		if (p->instruct.args[0].type == ARG_DIR
				&& p->instruct.args[1].type == ARG_NONE
				&& p->instruct.args[2].type == ARG_NONE)
			return (true);
	if (p->instruct.op == OP_AFF)
		if (p->instruct.args[0].type == ARG_REG
				&& p->instruct.args[1].type == ARG_NONE
				&& p->instruct.args[2].type == ARG_NONE)
			return (true);
	return (false);
}

bool	is_op_other_valid(t_process *p)
{
	if (p->instruct.op == OP_LIVE)
		if (p->instruct.args[0].type == ARG_DIR
				&& p->instruct.args[1].type == ARG_NONE
				&& p->instruct.args[2].type == ARG_NONE)
			return (true);
	if (p->instruct.op == OP_ADD)
		if (p->instruct.args[0].type == ARG_REG
				&& p->instruct.args[1].type == ARG_REG
				&& p->instruct.args[2].type == ARG_REG)
			return (true);
	if (p->instruct.op == OP_SUB)
		if (p->instruct.args[0].type == ARG_REG
				&& p->instruct.args[1].type == ARG_REG
				&& p->instruct.args[2].type == ARG_REG)
			return (true);
	return (false);
}

bool	is_l_ld_st_valid(t_process *p)
{
	static bool	g_valid_ld[ARG_MX][ARG_MX][ARG_MX];
	static bool	g_valid_lld[ARG_MX][ARG_MX][ARG_MX];
	static bool	g_valid_st[ARG_MX][ARG_MX][ARG_MX];

	g_valid_ld[ARG_DIR][ARG_REG][ARG_NONE] = true;
	g_valid_ld[ARG_IND][ARG_REG][ARG_NONE] = true;
	g_valid_lld[ARG_IND][ARG_REG][ARG_NONE] = true;
	g_valid_lld[ARG_DIR][ARG_REG][ARG_NONE] = true;
	g_valid_st[ARG_REG][ARG_IND][ARG_NONE] = true;
	g_valid_st[ARG_REG][ARG_REG][ARG_NONE] = true;
	if (p->instruct.op == OP_LD)
		return (g_valid_ld[p->instruct.args[0].type][
			p->instruct.args[1].type][p->instruct.args[2].type]);
	if (p->instruct.op == OP_LLD)
		return (g_valid_lld[p->instruct.args[0].type][
			p->instruct.args[1].type][p->instruct.args[2].type]);
	if (p->instruct.op == OP_ST)
		return (g_valid_st[p->instruct.args[0].type][
			p->instruct.args[1].type][p->instruct.args[2].type]);
	return (false);
}

bool	is_lldi_valid(t_process *p)
{
	static bool	g_valid_lldi[ARG_MX][ARG_MX][ARG_MX];

	g_valid_lldi[ARG_DIR][ARG_REG][ARG_REG] = true;
	g_valid_lldi[ARG_IND][ARG_REG][ARG_REG] = true;
	g_valid_lldi[ARG_REG][ARG_REG][ARG_REG] = true;
	g_valid_lldi[ARG_IND][ARG_DIR][ARG_REG] = true;
	g_valid_lldi[ARG_DIR][ARG_DIR][ARG_REG] = true;
	g_valid_lldi[ARG_REG][ARG_DIR][ARG_REG] = true;
	return (g_valid_lldi[p->instruct.args[0].type][
			p->instruct.args[1].type][p->instruct.args[2].type]);
}
