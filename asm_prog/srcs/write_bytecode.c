/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytecode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:52:20 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/18 15:31:03 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline void	print_op_args(t_lexem lex)
{
	printf("Args :\n");
	if (lex.encoding & 128 && lex.encoding & 64)
		printf("indirect number (%lld)\n", lex.args[0].nb);
	if ((lex.encoding & 128) && !(lex.encoding & 64))
		printf("direct number (%lld)\n", lex.args[0].nb);
	if (!(lex.encoding & 128) && (lex.encoding & 64))
		printf("register (r%d)\n", lex.args[0].reg);

	if (lex.encoding & 32 && lex.encoding & 16)
		printf("indirect number (%lld)\n", lex.args[1].nb);
	if ((lex.encoding & 32) && !(lex.encoding & 16))
		printf("direct number (%lld)\n", lex.args[1].nb);
	if (!(lex.encoding & 32) && (lex.encoding & 16))
		printf("register (r%d)\n", lex.args[1].reg);
	
	if (lex.encoding & 8 && lex.encoding & 4)
		printf("indirect number (%lld)\n", lex.args[2].nb);
	if ((lex.encoding & 8) && !(lex.encoding & 4))
		printf("direct number (%lld)\n", lex.args[2].nb);
	if (!(lex.encoding & 8) && (lex.encoding & 4))
		printf("register (r%d)\n", lex.args[1].reg);
}

static inline void	print_lexem(t_lexem lex)
{
	switch (lex.type)
	{
		case LEX_NAME_PROP:
			printf("NAME_PROP (%s)\n", lex.args[0].str);
			break;
		case LEX_COMMENT_PROP:
			printf("COMMENT_PROP (%s)\n", lex.args[0].str);
			break;
		case LEX_LABEL:
			printf("LABEL\n");
			break;
		case LEX_OP:
			printf("OPCODE (%s)\n", g_opnames[(int)lex.opcode]);
			print_op_args(lex);
	//		print_byte_as_bits(lex.encoding);
			break;
	}
}

static inline int	set_dir_size(t_env *env)
{
	static char		sizes[NB_OPS] = {4, 4, 4, 2, 2, 4, 2, 4, 2, 4, 4, 4, 2, 4, 4, 2};
	unsigned int	i;

	i = 0;
	while (i < env->nb_lex)
	{
		env->lexemes[i].dir_size = (char)sizes[(int)env->lexemes[i].type];
		i++;
	}
	return (0);
}


static inline void	write_indirect_number(int fd, t_lexem lex)
{
	
}

static inline void	write_direct_number()
{
		
}

static inline void	write_register()
{
		
}

static inline void	write_params(t_lexem lex, int fd)
{
	(void)fd;
	if (lex.encoding & 128 && lex.encoding & 64)
		write_indirect_number(fd, lex);
		printf("indirect number (%lld)\n", lex.args[0].nb);
	if ((lex.encoding & 128) && !(lex.encoding & 64))
		write_direct_number(fd, lex);
		printf("direct number (%lld)\n", lex.args[0].nb);
	if (!(lex.encoding & 128) && (lex.encoding & 64))
		write_register(fd, lex);
		printf("register (r%d)\n", lex.args[0].reg);

	if (lex.encoding & 32 && lex.encoding & 16)
		printf("indirect number (%lld)\n", lex.args[1].nb);
	if ((lex.encoding & 32) && !(lex.encoding & 16))
		printf("direct number (%lld)\n", lex.args[1].nb);
	if (!(lex.encoding & 32) && (lex.encoding & 16))
		printf("register (r%d)\n", lex.args[1].reg);
	
	if (lex.encoding & 8 && lex.encoding & 4)
		printf("indirect number (%lld)\n", lex.args[2].nb);
	if ((lex.encoding & 8) && !(lex.encoding & 4))
		printf("direct number (%lld)\n", lex.args[2].nb);
	if (!(lex.encoding & 8) && (lex.encoding & 4))
		printf("register (r%d)\n", lex.args[1].reg);
}

static inline void	write_encoding(unsigned char byte, int fd)
{
	print_byte_as_bits(byte);
//	byte = rev_bits(byte, true);
	write(fd, &byte, sizeof(char));
}

int					write_bytecode(t_env *env)
{
	unsigned int	i;
	int				fd;
	char			tmp;

	i = 0;
	if ((fd = open(env->file_name, O_CREAT|O_WRONLY, 0666)) < 0
		|| write_header(env, fd) != 0 || set_dir_size(env) != 0)
		return (-1);
	while (i < env->nb_lex)
	{
		if (env->lexemes[i].type == LEX_OP)
		{
			tmp = g_opcodes[(int)env->lexemes[i].opcode];
			write(fd, &tmp, sizeof(char));
			if (encoding_byte_pres(env->lexemes[i].opcode))
				write_encoding(env->lexemes[i].encoding, fd);
			write_params(env->lexemes[i], fd);
		}
		print_lexem(env->lexemes[i]);
		i++;
	}
	close(fd);
	return (0);
}

