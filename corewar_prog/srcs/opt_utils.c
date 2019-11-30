/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 22:18:40 by moguy             #+#    #+#             */
/*   Updated: 2019/11/30 01:34:41 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_dump(char *arg, unsigned int *j)
{
	unsigned int	i;
	long long int	dump;

	i = *j + 2;
	i = after_space(arg, i);
	if (!ft_isdigit(arg[i]) || (dump = ft_atoi(&arg[i])) < 1 || dump > INT_MAX)
		return (-1);
	while (ft_isdigit(arg[i]))
		i++;
	if (!ft_is_whitespace(arg[i]))
		return (-1);
	*j = i;
	return ((int)dump);
}
