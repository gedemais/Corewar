/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:48:40 by moguy             #+#    #+#             */
/*   Updated: 2019/10/26 22:43:24 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				free_env(t_env *env, char *arg)
{
	t_process	*tmp;

	tmp = NULL;
	if (arg)
		ft_strdel(&arg);
	if (env->process)
	{
		while (env->process->next)
		{
			tmp = env->process;
			env->process = env->process->next;
			ft_memdel((void**)&tmp);
		}
		ft_memdel((void**)&env->process);
	}
}

int				error(char *error_msg, char *err_msg, char *junk)
{
	if (junk)
		ft_strdel(&junk);
	if (error_msg)
		ft_putendl_fd(error_msg, STDERR_FILENO);
	if (err_msg)
		ft_putendl_fd(err_msg, STDERR_FILENO);
	return (1);
}

static inline int	vm(t_env *env, char *arg)
{
	if (get_data(env, arg))
		return (1);
	if (cw_loop(env))
		return (1);
	free_env(env, arg);
	return (0);
}

static inline void	init_env(t_env *env)
{
	ft_memset(env, 0, sizeof(t_env));
	env->cycle_to_die = CYCLE_TO_DIE;
}

int					main(int ac, char **av)
{
	t_env			env;
	char			*arg;

	if (ac > MAX_ARGS || ac < 2)
		return (error(TOO_MANY_ARGS, USAGE, NULL));	
	if (!(arg = merge_args(ac, av)))
		return (error(BAD_ARGS, USAGE, NULL));	
	init_env(&env);
	if (vm(&env, arg))
	{
		free_env(&env, arg);
		return (1);
	}
	return (0);
}
