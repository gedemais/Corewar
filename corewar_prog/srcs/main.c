i/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:48:40 by moguy             #+#    #+#             */
/*   Updated: 2019/10/16 11:02:03 by moguy            ###   ########.fr       */
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
			tmp = queue_process;
			queue_process = queue_process->next;
			if (tmp->r)
				ft_memdel(&tmp->r);
			ft_memdel(&tmp);
		}
		if (queue_process->r)
			ft_memdel(&queue_process->r);
			ft_memdel(&queue_process);
	}
}

void				free_env(t_env *env)
{
	t_process	*tmp;

	if (env->process)
	{
		while (env->process->next)
		{
			tmp = process;
			process = process->next;
			if (tmp->r)
				ft_memdel(&tmp->r);
			ft_memdel(&tmp);
		}
		if (process->r)
			ft_memdel(&process->r);
			ft_memdel(&process);
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
		return (error(USAGE, arg));	
	}
	ft_memset(&env, 0, sizeof(t_env));
	if (!(arg = merge_args(ac, av)))
	{
		ft_putendl_fd(BAD_ARGS, STDERR_FILENO);
		return (error(USAGE, arg));	
	}
	if (vm(&env, arg))
	{
		free_env(&env);
		return (1);
	}
	print_test(&env);
	free_env(&env);
	return (0);
}

void				print_test(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_players)
	{
		printf("magic = %d\n", env->player[i].magic);
		printf("id = %lld\n", env->player[i].id);
		i++;
	}
	i = 0;
	while (i < env->nb_players)
	{
		printf("file %u\n%s\n", i, env->files[i]);
		i++;
	}
//	printf("Arena :%s\n\n", env->arena);
	printf("nb_players : %u\n", env->nb_players);
	printf("dump : %lld\n", env->dump);
	printf("cycle_to_die : %u\n", env->cycle_to_die);
	printf("cycle_delta : %u\n", env->cycle_delta);
}
