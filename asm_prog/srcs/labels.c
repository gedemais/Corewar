#include "asm.h"

int	add_label(t_env *env, unsigned int i)
{
	i--;
	while (ft_isalnum(env->file[i]) && env->file[i] != '\n' && i > 0)
		i--;
	i++;
	printf("%s\n", &env->file[i]);
	env->labels[env->lab_i].ptr = &env->file[i];
	env->labels[env->lab_i].stick = i;
	env->lab_i++;
	return (0);
}

static inline unsigned int	count_labels(t_env *env)
{
	unsigned int	ret;
	unsigned int	i;

	ret = 0;
	i = 0;
	while (env->file[i])
	{
		while (env->file[i] && ft_is_whitespace(env->file[i]))
			i++;
		while (env->file[i] && (ft_isalnum(env->file[i]) || env->file[i] == '_'))
			i++;
		if (env->file[i] && env->file[i] == ':')
			if (env->file[i + 1] == '\n' || ft_is_whitespace(env->file[i + 1]))
			{
				add_label(env, i);
				ret++;
			}
		while (env->file[i] && !ft_is_whitespace(env->file[i]))
			i++;
	}
	return (ret);
}

int	init_labels(t_env *env)
{
	if ((env->nb_labels = count_labels(env)) == 0)
		return (0);
	if (!(env->labels = (t_label*)malloc(sizeof(t_label) * env->nb_labels)))
		return (-1);
	ft_memset(env->labels, 0, sizeof(t_label) * env->nb_labels);
	return (0);
}
