/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:35:34 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/17 16:31:44 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline short	get_label_pos(t_env *env, int label)
{
	unsigned int	i;
	int				j;

	i = 0;
	j = -1;
	if (label == -1)
		return (-1);
	while (i < env->nb_lex)
	{
		if (env->lexemes[i].type == LEX_LABEL)
			j++;
		if (j == label)
			return ((short)env->lexemes[i].start_byte);
		i++;
	}
	return (-1);
}

void				write_indirect_number(t_env *env, int fd, t_lexem lex, int param)
{
	short	val;

	if (lex.label[param] >= 0)
	{
		val = get_label_pos(env, lex.label[param]) - (short)lex.start_byte;
		printf("indirect label access to label n%d (%d)\n", lex.label[param], val);
	}
	else
	{
		val = (short)lex.args[param].nb;
		printf("indirect number %d\n", (int)lex.args[param].nb);
	}
	swap_short_bytes(&val);
	write(fd, &val, IND_SIZE);
}

void				write_direct_number(t_env *env, int fd, t_lexem lex, int param)
{
	int		val;
	short	addr;

	(void)env;
	if (lex.label[param] >= 0)
	{
		if (g_direct_size[(int)lex.opcode] == DIR_SIZE)
		{
			val = reverse_int_bytes((int)get_label_pos(env, lex.label[param]) - (int)lex.start_byte);
			write(fd, &val, DIR_SIZE);
		printf("direct label access to label n%d (%d)\n", lex.label[param], val);
		}
		else
		{
			addr = get_label_pos(env, lex.label[param]) - (short)lex.start_byte;
			swap_short_bytes(&addr);
			write(fd, &addr, IND_SIZE);
		printf("direct label access to label n%d (%d)\n", lex.label[param], addr);
		}
	}
	else
	{
		printf("direct number %d\n", (int)lex.args[param].nb);
		val = reverse_int_bytes((int)lex.args[param].nb);
		write(fd, &val, DIR_SIZE);
	}
}

void				write_register(int fd, t_lexem lex, int param)
{
	char	reg;

	reg = (char)lex.args[param].reg;
	printf("register %d\n", reg);
	write(fd, &reg, 1);
}
