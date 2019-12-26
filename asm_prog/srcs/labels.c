#include "asm.h"

bool						is_label_char(char c)
{
	unsigned int	i;

	i = 0;
	if (c == 0)
		return (false);
	while (LABEL_CHARS[i])
	{
		if (LABEL_CHARS[i] == c)
			return (true);
		i++;
	}
	return (false);
}

bool						is_label(t_env *env, char *label)
{
	unsigned int	i;
	size_t			len;

	i = 0;
	len = 0;
	while (is_label_char(label[len]))
		len++;
	while (i < env->nb_labels && env->labels[i].ptr)
	{
		if (len == env->labels[i].len)
			if (!ft_strncmp(label, env->labels[i].ptr, len))
				return (true);
		i++;
	}
	return (false);
}

static inline bool			check_presence(t_label *labels, unsigned int n, char *try, unsigned int *stick)
{
	unsigned int		i;
	size_t				len;
	size_t				try_len;

	i = 0;
	try_len = 0;
	while (is_label_char(try[try_len]))
		try_len++;
	while (i < n && labels[i].ptr)
	{
		len = 0;
		while (is_label_char(labels[i].ptr[len]))
			len++;
		if (len == try_len && !ft_strncmp(labels[i].ptr, try, len))
		{
			*stick = labels[i].stick;
			return (true);
		}
		i++;
	}
	return (false);
}

int							find_label_index(t_label *labs, t_token *tok, unsigned int nb_labels)
{
	unsigned int	offset;
	unsigned int	len;
	int				ret;
	int				i;

	i = 0;
	ret = -1;
	offset = (tok->type == TOK_DLABA || tok->type == TOK_LNUMBER) ? 2 : 1;
	while (i < (int)nb_labels)
	{
		len = 0;
		while (is_label_char(labs[i].ptr[len]))
			len++;
		if (len == labs[i].len && !ft_strncmp(&tok->ptr[offset], labs[i].ptr, len))
			ret = i;
		i++;
	}
	return (ret);
}

static inline unsigned int	count_labels(t_env *env)
{
	unsigned int	ret;
	unsigned int	i;

	i = 0;
	ret = 0;
	while (env->file[i])
	{
		cross_whitespace(env->file, &i);
		cross_names(env->file, &i);
		if (env->file[i] && env->file[i] == ':')
			if (env->file[i + 1] == '\n' || ft_is_whitespace(env->file[i + 1]))
				ret++;
		while (env->file[i] && !ft_is_whitespace(env->file[i]))
			i++;
	}
	return (ret);
}

static inline int			add_label(t_env *env, unsigned int i)
{
	static int		index = 0;
	unsigned int	len;

	len = 0;
	i--;
	while (is_label_char(env->file[i])
		&& env->file[i] != '\n' && i > 0)
		i--;
	i++;
	if (check_presence(env->labels, env->nb_labels, &env->file[i], &len)
		&& dup_label_err(env->file, i, len))
		return (-1);
	env->labels[env->lab_i].ptr = &env->file[i];
	env->labels[env->lab_i].stick = i;
	unsigned int tmp = i;
	while (env->file[i] != ':')
	{
		len++;
		i++;
	}
	printf("Loading %.*s[%d] (%d)\n", len + 1, &env->file[tmp], index, env->labels[env->lab_i].stick);
	env->labels[env->lab_i].len = len;
	env->lab_i++;
	index++;
	return (0);
}

static inline int			load_labels(t_env *env)
{
	unsigned int	i;

	i = 0;
//	printf("----------------------\nLOAD LABELS :\n");
	while (env->file[i])
	{
		cross_whitespace(env->file, &i);
		cross_names(env->file, &i);
		if (env->file[i] && env->file[i] == ':')
			if (env->file[i + 1] == '\n' || ft_is_whitespace(env->file[i + 1]))
				if (add_label(env, i) == -1)
					return (-1);
		while (env->file[i] && !ft_is_whitespace(env->file[i]))
			i++;
	}
	return (0);
}

int							init_labels(t_env *env)
{
	//printf("INIT LABELS\n--------------------------------------------\n");
	if ((env->nb_labels = count_labels(env)) == 0)
		return (0);
	if (!(env->labels = (t_label*)malloc(sizeof(t_label) * env->nb_labels)))
		return (-1);
	ft_memset(env->labels, 0, sizeof(t_label) * env->nb_labels);
	if (load_labels(env) != 0)
		return (-1);
	return (0);
}
