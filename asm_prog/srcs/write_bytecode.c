/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bytecode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:13:15 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/08 14:20:31 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

static inline void	print_fine(int size, char *path)
{
	ft_putstr("Binary successfully written at ");
	ft_putstr(BLUE);
	ft_putstr(path);
	ft_putstr(STOP);
	ft_putstr(" (");
	ft_putnbr(size);
	ft_putendl(" bytes)");
}

int					write_bytecode(t_env *env)
{
	unsigned int	i;
	int				fd;
	int				ret;

	i = 0;
	if ((ret = write_header(env, &fd)) != 0)
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
	print_fine(env->bin_size, env->bin_name);
	return (0);
}
