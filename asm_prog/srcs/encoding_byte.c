/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding_byte.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:15:23 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/17 18:29:50 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void print_byte_as_bits(char val) {
  for (int i = 7; 0 <= i; i--) {
    printf("%c ", (val & (1 << i)) ? '1' : '0');
  }
  printf("\n");
}

bool	encoding_byte_pres(char type)
{
	static bool bytes[NB_OPS] = {1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0};

	return (bytes[(int)type]);
}

char	encoding_byte(char byte, unsigned int param, int type)
{
	static int		pow[6] = {128, 64, 32, 16, 8, 4};

	if (type == TOK_REG) // register
		byte += pow[(param * 2) + 1];
	else if (type == TOK_NUMBER) // indirect
	{
		byte += pow[(param * 2)];
		byte += pow[(param * 2) + 1];
	}
	else if (type == TOK_LNUMBER) // direct
		byte += pow[(param * 2)];
	return (byte);
}
