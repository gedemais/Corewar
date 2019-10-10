#include "asm.h"

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
				ret++;
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
