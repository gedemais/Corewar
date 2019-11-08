/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:55:04 by moguy             #+#    #+#             */
/*   Updated: 2019/11/07 21:44:36 by unknown          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline int	get_file(t_env *env, char *arg, unsigned int *j)
{
	unsigned int	i;

	i = *j;
	if (arg[i] == '-' && !ft_strncmp(&arg[i], OPT_N, 3))
	{
		if (get_id(env, arg, &i, false))
			return (1);
		i = after_space(arg, i);
	}
	if (!ft_strncmp(&arg[i + get_name_len(&arg[i]) - 4], EXT, 4))
	{
		if (env->nb_pl > 3)
			return (error(TOO_MANY_PLAYERS, USAGE, NULL));
		if (loader(env, arg, &i))
			return (1);
		i = after_word(arg, i);
		env->nb_pl++;
	}	
	else
		return (error(BAD_ARGS, USAGE, NULL));
	*j = i;
	return (0);
}

static inline int	check_verbose(t_env *env, char *arg, unsigned int *j)
{
	unsigned int	i;
	long long int	nb;

	i = *j;
	if (arg[i + 1] == 'v' && ft_is_whitespace(arg[i + 2])
			&& (nb = ft_atoi(&arg[i + 3])) > 0 && nb < VERB_MAX)
	{
		env->verbose = (unsigned int)nb;
		i += 3;
		*j = after_word(arg, i);
		return (1);
	}
	return (0);
}

static inline int	get_opt(t_env *env, char *arg, unsigned int *j)
{
	unsigned int	i;
	bool			close_op;

	i = *j;
	close_op = false;
	while (arg[i] == '-' && !close_op)
	{
		if (arg[i + 1] == 'v' && check_verbose(env, arg, &i))
			i++;
		else if (arg[i + 1] == 'd' && ft_is_whitespace(arg[i + 2]))
		{
			env->opt[D] = true;
			if ((env->opt[DMP] = get_dump(arg, &i, 2)) < 0)
				return (error(BAD_DUMP, USAGE, NULL));
		}
		else if (!ft_strncmp(&arg[i], DUMP, 6) && env->opt[DMP] == 0)
		{
			if ((env->opt[DMP] = get_dump(arg, &i, 5)) < 0)
				return (error(BAD_DUMP, USAGE, NULL));
		}
		else if (!ft_strncmp(&arg[i], OPT_N, 3)
			|| !ft_strncmp(&arg[i + get_name_len(&arg[i]) - 4], EXT, 4))
			break ;
		else
			return (error(BAD_OPT, USAGE, NULL));
		i = after_space(arg, i);
	}
	*j = i;
	return (0);
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

int					get_data(t_env *env, char *arg)
{
	unsigned int	i;

	i = after_space(arg, 0);
	while (arg[i])
	{
		if (arg[i] == '-' && get_opt(env, arg, &i))
			return (1);
		if (get_file(env, arg, &i))
			return (1);
		i = after_space(arg, i);
	}
	if (get_id(env, arg, 0, true))
		return (1);
	if (check_too_high_id(env))
		return (error(BAD_ID, USAGE, NULL));
	return (0);
}
