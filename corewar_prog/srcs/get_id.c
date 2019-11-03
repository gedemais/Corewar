/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_id.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:48:16 by moguy             #+#    #+#             */
/*   Updated: 2019/11/02 23:15:04 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				find_new_id(t_env *env, unsigned int j)
{
	unsigned int	i;
	uint32_t		ret;

	i = 0;
	ret = 1;
	while (i < env->nb_pl + 1)
	{
		if (ret == env->player[i].id)
		{
			i = 0;
			ret++;
		}
		else
			i++;
	}
	env->player[j].id = ret;
}

static inline int	check_too_high_id(t_env *env)
{
	unsigned int	i;
	
	i = 0;
	while (i < env->nb_pl)
	{
		if (env->player[i].id > env->nb_pl || env->player[i].id < 1)
			return (1);
		i++;
	}
	return (0);
}

static inline void	check_id(t_env *env)
{
	unsigned int	i;
	
	i = 0;
	while (i < env->nb_pl)
	{
		if (env->player[i].id == env->player[env->nb_pl].id)
		{
			env->player[i].id = 0;
			find_new_id(env, i);
		}
		i++;
	}
}

int					get_id(t_env *env, char *arg, unsigned int *j)
{
	static bool		opt_n[4] = {false};
	long long int	id;
	unsigned int	i;

	i = after_space(arg, *j + 3);
	if (!ft_isdigit(arg[i]) || (id = ft_atoi(&arg[i])) < 1 || id > 4)
		return (error(BAD_ID, USAGE, NULL));
	env->player[env->nb_pl].id  = (uint32_t)id;
	*j = i + 2;
	if (opt_n[env->player[env->nb_pl].id - 1] == false)
		opt_n[env->player[env->nb_pl].id - 1] = true;
	else 
		return (error(SAME_ID, USAGE, NULL));
	check_id(env);
	if (check_too_high_id(env))
		return (1);
	return (0);
}
