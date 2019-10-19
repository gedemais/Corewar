/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:58:18 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/19 23:36:57 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	reverse_bits(char buff[LBE_BUFFER], int num)
{
	int		swapped;

	swapped = ((num >> 24) & 0xff) |
		((num << 8) & 0xff0000) |
		(int)((num >> 8) & 0xff00) |
		(int)((num << 24) & (int)0xff000000);
	ft_memcpy(&buff[0], &swapped, sizeof(int));
}

unsigned char rev_bits(unsigned char b, bool shift)
{
	b = (unsigned char)((b & 0xF0) >> 4 | (b & 0x0F) << 4);
	b = (unsigned char)((b & 0xCC) >> 2 | (b & 0x33) << 2);
	b = (unsigned char)((b & 0xAA) >> 1 | (b & 0x55) << 1);
	(void)shift;
	if (shift)
		b = (unsigned char)(b << 2);
	return (b);
}

static inline int	get_op_size(t_lexem *lex)
{
	int		ret;

	ret = 0;
	if (lex->encoding & 128 && lex->encoding & 64)
		ret += IND_SIZE;
	if ((lex->encoding & 128) && !(lex->encoding & 64))
		ret += g_direct_size[(int)lex->opcode];
	if (!(lex->encoding & 128) && (lex->encoding & 64))
		ret++;

	if (lex->encoding & 32 && lex->encoding & 16)
		ret += IND_SIZE;
	if ((lex->encoding & 32) && !(lex->encoding & 16))
		ret += g_direct_size[(int)lex->opcode];
	if (!(lex->encoding & 32) && (lex->encoding & 16))
		ret++;

	if (lex->encoding & 8 && lex->encoding & 4)
		ret += IND_SIZE;
	if ((lex->encoding & 8) && !(lex->encoding & 4))
		ret += g_direct_size[(int)lex->opcode];
	if (!(lex->encoding & 8) && (lex->encoding & 4))
		ret++;

	return (ret);
}

static inline int	compute_bytecode_size(t_env *env)
{
	unsigned int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < env->nb_lex)
	{
		if (env->lexemes[i].type == LEX_LABEL)
		{
			env->lexemes[i].start_byte = (unsigned int)ret;
			printf("label start : %u\n", env->lexemes[i].start_byte);
		}
		else if (env->lexemes[i].type == LEX_OP)
		{
			print_lexem(env->lexemes[i]);
		env->lexemes[i].start_byte = (unsigned int)ret;
			ret++; // byte de l'opcode
			if (env->lexemes[i].code) // byte d'encoding
				ret++;
			ret += get_op_size(&env->lexemes[i]); // Taille des arguments
			printf("ret = %d\n", ret);
		}
		i++;
	}
	return (ret);
}

static inline char	*get_lex_string(t_env *env, char id)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_lex)
	{
		if (env->lexemes[i].type == id)
			return (ft_strdup(env->lexemes[i].args[0].str));
		i++;
	}
	return (NULL);
}

int		write_header(t_env *env, int fd)
{
	char	buff[HEADER_SIZE];
	char	lbe_buff[LBE_BUFFER];

	if (!(env->p_name = get_lex_string(env, LEX_NAME_PROP))
			|| !(env->p_comment = get_lex_string(env, LEX_COMMENT_PROP)))
		return (-1);
	env->file_size = compute_bytecode_size(env);
	printf("Bytecode size : %d\n", env->file_size);
	reverse_bits(lbe_buff, COREWAR_EXEC_MAGIC);
	write(fd, lbe_buff, LBE_BUFFER);//magic number

	ft_memset(buff, 0, sizeof(char) * HEADER_SIZE);
	ft_strcpy(buff, env->p_name);
	write(fd, buff, PROG_NAME_LENGTH);//name

	ft_memset(lbe_buff, PADDING_VALUE, sizeof(char) * LBE_BUFFER);
	write(fd, lbe_buff, LBE_BUFFER);//padding 1

	reverse_bits(lbe_buff, env->file_size);
	write(fd, lbe_buff, LBE_BUFFER);//instruction section size

	ft_memset(buff, 0, sizeof(char) * HEADER_SIZE);
	ft_strcpy(buff, env->p_comment);
	write(fd, buff, COMMENT_LENGTH);//comment

	ft_memset(lbe_buff, PADDING_VALUE, sizeof(char) * LBE_BUFFER);
	write(fd, lbe_buff, LBE_BUFFER);//padding 2
	return (0);
}
