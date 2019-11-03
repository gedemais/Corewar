/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:55:04 by moguy             #+#    #+#             */
/*   Updated: 2019/11/03 07:24:45 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline int	get_file(t_env *env, char *arg, unsigned int *j)
{
	unsigned int	i;

	i = *j;
	if (arg[i] == '-' && !ft_strncmp(&arg[i], OPT_N, 3))
	{
		if (get_id(env, arg, &i))
			return (error(BAD_ID, USAGE, NULL));
		i = after_space(arg, i);
	}
	if (!ft_strncmp(&arg[i + get_name_len(&arg[i]) - 4], EXT, 4))
	{
		if (env->nb_pl > 3)
			return (error(TOO_MANY_PLAYERS, USAGE, NULL));
		if (env->player[env->nb_pl].id == 0)
			find_new_id(env, env->nb_pl);
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

	i = *j;
	if (arg[i + 1] == 'v' && ft_is_whitespace(arg[i + 2])
			&& ft_isdigit(arg[i + 3]) && ft_is_whitespace(arg[i + 4])
			&& (arg[i + 3] - '0') < 6 && (arg[i + 3] - '0') > 0)
	{
		env->verbose[arg[i + 3] - '0'] = true;
		i += 4;
		*j = i;
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
		else if (!ft_strncmp(&arg[i], DUMP, 6) && env->opt[DMP] == 0)
		{
			if ((env->opt[DMP] = get_dump(arg, &i)) < 0)
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
	return (0);
}
