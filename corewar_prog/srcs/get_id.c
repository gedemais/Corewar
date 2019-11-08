/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_id.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:48:16 by moguy             #+#    #+#             */
/*   Updated: 2019/11/08 01:51:45 by unknown          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline void			give_id(t_env *env, unsigned int i, unsigned int j,
		u_int8_t opt_n)
{
	while (i < env->nb_pl)
	{
		if (env->player[i].id == 0)
		{
			while (j < 5)
			{
				if (!(opt_n & (1 << j)))
				{
					env->player[i].id = (u_int32_t)j;
					j++;
					break ;
				}
				j++;
			}
		}
		i++;
	}
}

static inline u_int8_t			ft_power(u_int8_t nb, u_int8_t pow)
{
	u_int8_t	tmp;

	tmp = nb;
	if (pow < 1)
		return (0);
	while (pow > 1)
	{
		tmp *= nb;
		pow--;
	}
	return (tmp);
}

int					get_id(t_env *env, char *arg, unsigned int *j, bool end)
{
	static u_int8_t	opt_n = 0;
	long long int	id;
	unsigned int	i;

	if (end)
	{
		give_id(env, 0, 1, opt_n);
		return (0);
	}
	i = after_space(arg, *j + 3);
	if (!ft_isdigit(arg[i]) || (id = ft_atoi(&arg[i])) < 1 || id > 4)
		return (error(BAD_ID, USAGE, NULL));
	env->player[env->nb_pl].id  = (u_int32_t)id;
	*j = i + 2;
	if (!(opt_n & (1 << env->player[env->nb_pl].id)))
		opt_n |= ft_power(2, (u_int8_t)env->player[env->nb_pl].id);
	else 
		return (error(SAME_ID, USAGE, NULL));
	return (0);
}
