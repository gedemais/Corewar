/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:48:40 by moguy             #+#    #+#             */
/*   Updated: 2019/10/31 19:26:23 by moguy            ###   ########.fr       */
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

static inline void	introducing_champions(t_env *env)
{
	unsigned int	i;
	
	i = 1;
	if (env->nb_pl == 1)
		printf("The contestant is alone, he is %s with the id %u.\n",
				env->player[0].name, env->player[0].id);
	else
		printf("The contestants are %u :-%s with the id %u.\n", env->nb_pl,
				env->player[0].name, env->player[0].id);
	while (i < env->nb_pl)
	{
		printf("                        -%s with the id %u\n.",
				env->player[i].name, env->player[i].id);
		i++;
	}
}

static inline int	vm(t_env *env, char *arg)
{
	if (get_data(env, arg))
		return (1);
	introducing_champions(env);
	if (cw_loop(env))
		return (1);
	free_env(env, arg);
	return (0);
}

int					main(int ac, char **av)
{
	t_env			env;
	char			*arg;

	if (ac > MAX_ARGS || ac < 2)
		return (error(TOO_MANY_ARGS, USAGE, NULL));	
	if (!(arg = merge_args(ac, av)))
		return (error(BAD_ARGS, USAGE, NULL));	
	ft_memset(&env, 0, sizeof(t_env));
	env.cycle_to_die = CYCLE_TO_DIE;
	if (vm(&env, arg))
	{
		free_env(&env, arg);
		return (1);
	}
	return (0);
}
