/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:48:40 by moguy             #+#    #+#             */
/*   Updated: 2019/10/13 17:44:29 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_test(t_env *env, char *arg)
{
	unsigned int	i;

	i = 0;
	printf("arg = %s\n\n", arg);
	while (i < env->nb_players)
	{
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

static inline int	vm(t_env *env, char *arg)
{
	env->cycle_to_die = CYCLE_TO_DIE;
	env->cycle_delta = CYCLE_DELTA;
	if (get_opt_champ(env, arg))
	{
		ft_putendl_fd(BAD_ARGS, STDERR_FILENO);
		ft_putendl_fd(USAGE, STDERR_FILENO);
		return (1);
	}
	return (0);
}

int					main(int ac, char **av)
{
	t_env			env;
	char			*arg;

	if (ac > MAX_ARGS || ac < 3)
	{
		ft_putendl_fd(TOO_MANY_ARGS, STDERR_FILENO);
		ft_putendl_fd(USAGE, STDERR_FILENO);
		return (1);
	}
	ft_memset(&env, 0, sizeof(t_env));
	if (!(arg = merge_args(ac, av)))
	{
		ft_putendl_fd(BAD_ARGS, STDERR_FILENO);
		ft_putendl_fd(USAGE, STDERR_FILENO);
		ft_strdel(&arg);
		return (1);
	}
	if (vm(&env, arg))
	{
		ft_strdel(&arg);
		return (1);
	}
	print_test(&env, arg);
	ft_strdel(&arg);
	return (0);
}
