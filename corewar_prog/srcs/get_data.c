/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:55:04 by moguy             #+#    #+#             */
/*   Updated: 2020/02/05 11:58:55 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline int	get_file(t_env *env, char *arg, unsigned int *j)
{
	unsigned int	i;

	i = *j;
	if (!ft_strncmp(&arg[i], OPT_N, 3))
	{
		if (get_id(env, arg, &i, false))
			return (1);
		i = after_space(arg, i);
	}
	if (!ft_strncmp(&arg[i + get_name_len(&arg[i]) - 4], EXT, 4))
	{
		if (env->nb_pl > 3)
			return (error(singleton_str(3), USAGE, NULL));
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

	i = *j + 3;
	nb = ft_atoi(&arg[i]);
	if (nb > 0 && nb <= VERB_MAX)
	{
		env->opt[V] = (int)nb;
		*j = after_word(arg, i);
		return (0);
	}
	else
		return (1);
}

static inline int	help_get_opt(t_env *env, char *arg, unsigned int *j,
		int ret)
{
	unsigned int	i;

	i = *j;
	if (!ft_strncmp(&arg[i], OPT_A, 3) && env->opt[A] == false && (i += 3))
		env->opt[A] = true;
	else if (!ft_strncmp(&arg[i], OPT_D, 3) && env->opt[D] == false)
	{
		if ((env->opt[D] = get_dump(arg, &i)) < 0)
			return (error(BAD_DUMP, USAGE, NULL));
	}
	else if (!ft_strncmp(&arg[i], OPT_S, 3) && env->opt[D] == false)
	{
		env->opt[S] = true;
		if ((env->opt[D] = get_dump(arg, &i)) == 0)
			return (error(BAD_DUMP, USAGE, NULL));
	}
	else if (!ft_strncmp(&arg[i], OPT_N, 3)
		|| ((ret = (int)i + (int)get_name_len(&arg[i]) - 4) >= 0
			&& !ft_strncmp(&arg[ret], EXT, 4)))
		return (-1);
	else
		return (error(BAD_OPT, USAGE, NULL));
	*j = i;
	return (0);
}

static inline int	get_opt(t_env *env, char *arg, unsigned int *j)
{
	unsigned int	i;
	int				ret;

	i = *j;
	ret = 0;
	while (arg[i] == '-')
	{
		if (!ft_strncmp(&arg[i], OPT_V, 3) && env->opt[V] == 0)
		{
			if (check_verbose(env, arg, &i))
				return (error(BAD_VERBOSE, USAGE, NULL));
		}
		else
			ret = help_get_opt(env, arg, &i, ret);
		if (ret == -1)
			break ;
		else if (ret == 1)
			return (1);
		i = after_space(arg, i);
	}
	*j = i;
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
