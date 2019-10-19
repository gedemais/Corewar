/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytecode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:52:20 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/19 23:46:48 by gedemais         ###   ########.fr       */
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
/*
static inline int	set_dir_size(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_lex)
	{
		env->lexemes[i].dir_size = (char)sizes[(int)env->lexemes[i].type];
		i++;
	}
	return (0);
}*/

static inline int	label_pos(t_env *env, int label)
{
	unsigned int	i;
	int				j;

	i = 0;
	j = 0;
	while (i < env->nb_lex)
	{
		if (env->lexemes[i].type == LEX_LABEL)
			j++;
		if (j == label)
			return ((int)env->lexemes[i].start_byte);
		i++;
	}
	return (-1);
}

static inline void	write_indirect_number(t_env *env, int fd, t_lexem lex, int param)
{
	unsigned short	val;
	char			rev[2];
	char			tmp;

	if (lex.label[param] >= 0)
	{
		val = (unsigned short)(label_pos(env, lex.label[param]) - (int)lex.start_byte);
		ft_memcpy(&rev[0], &val, IND_SIZE);
		tmp = rev[0];
		rev[0] = rev[1];
		rev[1] = tmp;
		write(fd, &rev[0], IND_SIZE);
		printf("label %d : val = %d - %d\n", lex.label[param], label_pos(env, lex.label[param]), (int)lex.start_byte);
	}
	else
	{
		val = (unsigned short)lex.args[param].nb;
		write(fd, &val, IND_SIZE);
	}
}

static inline void	write_direct_number(t_env *env, int fd, t_lexem lex, int param)
{
	char			buff[LBE_BUFFER];
	char			rev[2];
	char			tmp;
	int				val;

	val = 0;
	if (lex.label[param] >= 0)
	{
		val = (unsigned short)(label_pos(env, lex.label[param]) - (int)lex.start_byte);
		ft_memcpy(&rev[0], &val, IND_SIZE);
		tmp = rev[0];
		rev[0] = rev[1];
		rev[1] = tmp;
		write(fd, &rev[0], IND_SIZE);
	}
	else
	{
		val = g_direct_size[(int)lex.opcode] == 4 ? (int)lex.args[param].nb : (short)lex.args[param].nb;
		reverse_bits(buff, val);
		write(fd, &buff, (size_t)g_direct_size[(int)lex.opcode]);
	}
}

static inline void	write_register(int fd, t_lexem lex, int param)
{
	char	reg;

	reg = (char)lex.args[param].reg;
	write(fd, &reg, 1);
}

static inline void	write_params(t_env *env, t_lexem lex, int fd)
{
	(void)fd;
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
	printf("---------------------------------------------------\nWRITE_BYTECODE\n");
	if ((fd = open(env->file_name, O_CREAT|O_WRONLY, 0666)) < 0
		|| write_header(env, fd) != 0)
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
