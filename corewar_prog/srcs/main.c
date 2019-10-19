/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:48:40 by moguy             #+#    #+#             */
/*   Updated: 2019/10/19 14:26:57 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				free_env(t_env *env)
{
	t_process	*tmp;

	tmp = NULL;
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

int				error(char *error_msg, char *file)
{
	if (file)
		ft_strdel(&file);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	return (1);
}

static inline int	vm(t_env *env, char *arg)
{
	if (get_opt_champ(env, arg))
	{	
		ft_putendl_fd(BAD_ARGS, STDERR_FILENO);
		return (error(USAGE, arg));
	}
	if (cw_loop(env))
		return (error(VM_ERR, arg));
	ft_strdel(&arg);
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
	{
		ft_putendl_fd(TOO_MANY_ARGS, STDERR_FILENO);
		return (error(USAGE, NULL));	
	}
	init_env(&env);
	if (!(arg = merge_args(ac, av)))
	{
		ft_putendl_fd(BAD_ARGS, STDERR_FILENO);
		return (error(USAGE, NULL));	
	}
	if (vm(&env, arg))
	{
		free_env(&env);
		return (1);
	}
	free_env(&env);
	return (0);
}
