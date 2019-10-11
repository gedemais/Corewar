#include "vm.h"

static inline int	get_opt(t_env *env, char *arg)
{
	if (loader(env, arg) != 0)
		return (-1);
	return (0);
}

static inline int	vm(t_env *env, char *arg)
{
	if (get_opt(env, arg) != 0)
		return (-1);
	return (0);
}

int			main(int ac, char **av)
{
	t_env	env;
	char	*arg;

	if (ac > MAX_ARGS)
	{
		ft_putendl_fd(USAGE);
		return (1);
	}
	ft_memset(&env, 0, sizeof(env));
	if (!(arg = merge_args(ac, av)))
	{
		ft_strdel(&arg);
		return (1);
	}
	if (vm(env, arg) != 0)
	{
		ft_strdel(&arg);
		free_env(&env);
		return (1);
	}
	return (0);
}
