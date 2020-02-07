/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:48:40 by moguy             #+#    #+#             */
/*   Updated: 2020/02/07 05:31:27 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static const char	g_tab_usage[] = "Usage: ./corewar [-d N -s N -v N | "
"-ncurses --stealth] [-a] [-n N1] <champion1.cor> <...>\n"
"    -a        : Prints output from \"aff\" (Default is to hide it)\n"
"#### TEXT OUTPUT MODE #######################################################"
"##########################\n"
"    -d N      : Dumps memory after N cycles then exits\n"
"    -n N      : Give an ID to the following player, it must be between 1 and "
"the number of contestants\n"
"    -s N      : Runs N cycles, dumps memory, pauses, then repeats\n"
"    -v N      : Verbosity levels, can be added together to enable several\n"
"                - 0 : Show only essentials\n"
"                - 1 : Show lives\n"
"                - 2 : Show cycles\n"
"                - 4 : Show operations (Params are NOT litteral ...)\n"
"                - 8 : Show deaths\n"
"                - 16 : Show PC movements (Except for jumps)\n"
"#############################################################################"
"##########################\n";

void				free_env(t_env *env, char *arg)
{
	t_process		*tmp;

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

int					error(char *error_msg, char *err_msg, char *junk)
{
	if (junk)
		ft_strdel(&junk);
	if (error_msg)
		ft_putendl_fd(error_msg, STDERR_FILENO);
	if (err_msg && !ft_strcmp(err_msg, USAGE))
		ft_putstr_fd(&g_tab_usage[0], 2);
	else if (err_msg)
		ft_putendl_fd(err_msg, STDERR_FILENO);
	return (1);
}

static inline void	introducing_champions(t_env *env)
{
	unsigned int	i;

	i = 0;
	env->arg.str = "Introducing contestants...\n";
	buffer_cor(env->arg, 0, 0);
	while (i < env->nb_pl)
	{
		env->arg.str = "* Player ";
		buffer_cor(env->arg, 0, 0);
		env->arg.u = env->player[i].id;
		buffer_cor(env->arg, 2, 0);
		env->arg.str = ", weighing ";
		buffer_cor(env->arg, 0, 0);
		env->arg.u = env->player[i].size;
		buffer_cor(env->arg, 2, 0);
		env->arg.str = " bytes, \"";
		buffer_cor(env->arg, 0, 0);
		env->arg.str = env->player[i].name;
		buffer_cor(env->arg, 0, 0);
		env->arg.str = "\" (\"";
		buffer_cor(env->arg, 0, 0);
		env->arg.str = env->player[i].com;
		buffer_cor(env->arg, 0, 0);
		env->arg.str = "\") !\n";
		buffer_cor(env->arg, 0, 0);
		i++;
	}
}

static inline int	vm(t_env *env, char *arg)
{
	if (get_data(env, arg))
		return (1);
	introducing_champions(env);
	if (init_arena(env))
		return (1);
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
