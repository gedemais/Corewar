/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:48:40 by moguy             #+#    #+#             */
/*   Updated: 2019/10/16 12:26:55 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline void	free_queue(t_env *env)
{
	t_process	*tmp;

	if (env->queue_process)
	{
		while (env->queue_process->next)
		{
			tmp = env->queue_process;
			env->queue_process = env->queue_process->next;
			if (tmp->r)
				ft_memdel((void**)&tmp->r);
			ft_memdel((void**)&tmp);
		}
		if (env->queue_process->r)
			ft_memdel((void**)&env->queue_process->r);
			ft_memdel((void**)&env->queue_process);
	}
}

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
			if (tmp->r)
				ft_memdel((void**)&tmp->r);
			ft_memdel((void**)&tmp);
		}
		if (env->process->r)
			ft_memdel((void**)&env->process->r);
			ft_memdel((void**)&env->process);
	}
	free_queue(env);
}

static inline int	vm(t_env *env, char *arg)
{
	env->cycle_to_die = CYCLE_TO_DIE;
	if (get_opt_champ(env, arg))
	{
		
		ft_putendl_fd(BAD_ARGS, STDERR_FILENO);
		return (error(USAGE, arg));
	}
//	if (cw_loop(env))
//		return (error(VM_ERR, arg));
	ft_strdel(&arg);
	return (0);
}

int					main(int ac, char **av)
{
	t_env			env;
	char			*arg;

	if (ac > MAX_ARGS || ac < 3)
	{
		ft_putendl_fd(TOO_MANY_ARGS, STDERR_FILENO);
		return (error(USAGE, NULL));	
	}
	ft_memset(&env, 0, sizeof(t_env));
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
