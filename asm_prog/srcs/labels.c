#include "asm.h"

bool						is_label(t_env *env, char *label)
{
	unsigned int	i;
	size_t			len;

	i = 0;
	len = 0;
	while (label[len] && (ft_isalnum(label[len]) || label[len] == '_'))
		len++;
	while (i < env->nb_labels)
	{
		if (len == env->labels[i].len)
			if (!ft_strncmp(label, env->labels[i].ptr, len))
				return (true);
		i++;
	}
	return (false);
}

int							add_label(t_env *env, unsigned int i)
{
	unsigned int	len;

	len = 0;
	i--;
	while ((ft_isalnum(env->file[i]) || env->file[i] == '_')
		&& env->file[i] != '\n' && i > 0)
		i--;
	i++;
	env->labels[env->lab_i].ptr = &env->file[i];
	env->labels[env->lab_i].stick = i;
	while (env->file[i] != ':')
	{
		len++;
		i++;
	}
	env->labels[env->lab_i].len = len;
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
				ret++;
		while (env->file[i] && !ft_is_whitespace(env->file[i]))
			i++;
	}
	return (ret);
}

static inline int			load_labels(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (env->file[i])
	{
		while (env->file[i] && ft_is_whitespace(env->file[i]))
			i++;
		while (env->file[i] && (ft_isalnum(env->file[i]) || env->file[i] == '_'))
			i++;
		if (env->file[i] && env->file[i] == ':')
			if (env->file[i + 1] == '\n' || ft_is_whitespace(env->file[i + 1]))
				add_label(env, i);
		while (env->file[i] && !ft_is_whitespace(env->file[i]))
			i++;
	}
	return (0);
}

int							init_labels(t_env *env)
{
	if (DEBUG_MODE)
		DBPRINT("Init_labels...");

	if ((env->nb_labels = count_labels(env)) == 0)
		return (0);
	if (!(env->labels = (t_label*)malloc(sizeof(t_label) * env->nb_labels)))
		return (-1);
	ft_memset(env->labels, 0, sizeof(t_label) * env->nb_labels);
	if (load_labels(env) != 0)
		return (-1);
	if (DEBUG_MODE)
	{
		printf("%u labels found...", env->nb_labels);
		DBPRINT("Fine !\n\n");
	}
	return (0);
}
