/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 18:01:39 by moguy             #+#    #+#             */
/*   Updated: 2019/10/23 18:54:55 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

int		main(void)
{
	int		nb;
	short	n;

	nb = 0;
	n = 0;
	n = hex_conv2(0b1111, 0b1111);
	nb = hex_conv4(0b0000, 0b0000, 0b1111, 0b1111);
	printf("nb = %d\nn = %hd\n", nb, n);
	n = hex_conv2(0b0011, 0b1111);
	nb = hex_conv4(0b0000, 0b1111, 0b1111, 0b1111);
	printf("nb = %d\nn = %hd\n", nb, n);
	n = hex_conv2(0b0000, 0b1111);
	nb = hex_conv4(0b1111, 0b1111, 0b1111, 0b1111);
	printf("nb = %d\nn = %hd\n", nb, n);
	nb  = nb_arg(14);
	printf("nb_arg = %d\n", nb);
	nb = wait_cycle(15);
	printf("wait_cycle = %d\n", nb);
}

/*
int		main(void)
{
	if (carry_flag(1) == 0)
		ft_putendl("vrai");
	else
		ft_putendl("faux");
	if (carry_flag(6) == 1)
		ft_putendl("vrai");
	else
		ft_putendl("faux");
	if (carry_flag(11) == 0)
		ft_putendl("vrai");
	else
		ft_putendl("faux");
	if (carry_flag(14) == 1)
		ft_putendl("vrai");
	else
		ft_putendl("faux");
	if (direct_size(1) == 0)
		ft_putendl("vrai");
	else
		ft_putendl("faux");
	if (direct_size(6) == 0)
		ft_putendl("vrai");
	else
		ft_putendl("faux");
	if (direct_size(11) == 1)
		ft_putendl("vrai");
	else
		ft_putendl("faux");
	if (direct_size(14) == 1)
		ft_putendl("vrai");
	else
		ft_putendl("faux");
	if (encoding_byte(1) == 0)
		ft_putendl("vrai");
	else
		ft_putendl("faux");
	if (encoding_byte(6) == 1)
		ft_putendl("vrai");
	else
		ft_putendl("faux");
	if (encoding_byte(11) == 1)
		ft_putendl("vrai");
	else
		ft_putendl("faux");
	if (encoding_byte(16) == 1)
		ft_putendl("vrai");
	else
		ft_putendl("faux");
}*/
