/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:20:41 by moguy             #+#    #+#             */
/*   Updated: 2019/10/30 14:16:42 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int		after_word(char *arg, unsigned int i)
{
	if (!arg)
		return (0);
	while (arg[i] && !ft_is_whitespace(arg[i]))
		i++;
	return (i);
}
