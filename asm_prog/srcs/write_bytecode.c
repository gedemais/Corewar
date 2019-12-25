/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytecode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:13:15 by gedemais          #+#    #+#             */
/*   Updated: 2019/12/26 00:36:47 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_op_args(t_lexem lex)
{
	if (lex.encoding & 128 && lex.encoding & 64)
		printf("indirect number (%lld) ", lex.args[0].nb);
	if ((lex.encoding & 128) && !(lex.encoding & 64))
		printf("direct number (%lld) ", lex.args[0].nb);
	if (!(lex.encoding & 128) && (lex.encoding & 64))
		printf("register (r%d) ", lex.args[0].reg);
	if (lex.label[0] != -1)
		printf("L%d ", lex.label[0]);

	if (lex.encoding & 32 && lex.encoding & 16)
		printf("indirect number (%lld) ", lex.args[1].nb);
	if ((lex.encoding & 32) && !(lex.encoding & 16))
		printf("direct number (%lld) ", lex.args[1].nb);
	if (!(lex.encoding & 32) && (lex.encoding & 16))
		printf("register (r%d) ", lex.args[1].reg);
	if (lex.label[1] != -1)
		printf("L%d ", lex.label[1]);
	
	if (lex.encoding & 8 && lex.encoding & 4)
		printf("indirect number (%lld) ", lex.args[2].nb);
	if ((lex.encoding & 8) && !(lex.encoding & 4))
		printf("direct number (%lld) ", lex.args[2].nb);
	if (!(lex.encoding & 8) && (lex.encoding & 4))
		printf("register (r%d) ", lex.args[2].reg);
	if (lex.label[2] != -1)
		printf("L%d ", lex.label[2]);
}

void	print_lexem(t_lexem lex)
{
	switch (lex.type)
	{
		case LEX_NAME_PROP:
			printf("NAME_PROP (%s)", lex.args[0].str);
			break;
		case LEX_COMMENT_PROP:
			printf("COMMENT_PROP (%s)", lex.args[0].str);
			break;
		case LEX_LABEL:
			printf("LABEL");
			break;
		case LEX_OP:
			printf("OPCODE (%s)->", g_opnames[(int)lex.opcode]);
			print_op_args(lex);
			print_byte_as_bits(lex.encoding);
			break;
	}
	printf("\n");
}

static inline void	write_params(t_env *env, t_lexem lex, int fd)
{
	if (lex.encoding & 128 && lex.encoding & 64)
		write_indirect_number(env, fd, lex, 0);
	if ((lex.encoding & 128) && !(lex.encoding & 64))
		write_direct_number(env, fd, lex, 0);
	if (!(lex.encoding & 128) && (lex.encoding & 64))
		write_register(fd, lex, 0);

	if (lex.encoding & 32 && lex.encoding & 16)
		write_indirect_number(env, fd, lex, 1);
	if ((lex.encoding & 32) && !(lex.encoding & 16))
		write_direct_number(env, fd, lex, 1);
	if (!(lex.encoding & 32) && (lex.encoding & 16))
		write_register(fd, lex, 1);

	if (lex.encoding & 8 && lex.encoding & 4)
		write_indirect_number(env, fd, lex, 2);
	if ((lex.encoding & 8) && !(lex.encoding & 4))
		write_direct_number(env, fd, lex, 2);
	if (!(lex.encoding & 8) && (lex.encoding & 4))
		write_register(fd, lex, 2);
}

int					write_bytecode(t_env *env)
{
	unsigned int	i;
	int				fd;

	i = 0;
	if (write_header(env, &fd) != 0)
		return (-1);
	while (i < env->nb_lex)
	{
		if (env->lexemes[i].type == LEX_OP)
		{
			write(fd, &g_opcodes[(int)env->lexemes[i].opcode], 1);
			if (encoding_byte_pres(env->lexemes[i].opcode))
			write(fd, &env->lexemes[i].encoding, 1);
			write_params(env, env->lexemes[i], fd);
		}
		i++;
	}
	close(fd);
	return (0);
}
