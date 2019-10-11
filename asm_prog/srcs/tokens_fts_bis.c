#include "asm.h"

char	get_tok_opcode(t_env *env, char *stream, unsigned int *i)
{
	unsigned int	j;
	size_t		size;

	(void)env;
	j = 0;
	while (j < NB_OPS)
	{
		size = ft_strlen(g_opnames[j]);
		if (ft_strncmp(g_opnames[j], stream, size) == 0
			&& ft_is_whitespace(stream[size]))
		{
			*i += size;
			return (TOK_OPCODE);
		}
		j++;
	}
	return (0);
}

char	get_tok_separator(t_env *env, char *stream, unsigned int *i)
{
	(void)env;
	if (FCHAR == ',')
	{
		*i += 1;
		return (TOK_SEPARATOR);
	}
	return (0);
}

char	get_tok_label(t_env *env, char *stream, unsigned int *i)
{
	(void)env;
	unsigned int	j;

	j = 0;
	if (!ft_isalnum(FCHAR))
		return (0);
	while (stream[j] && (ft_isalnum(stream[j]) || stream[j] == '_'))
		j++;
	if (stream[j] != ':')
		return (0);
	
	// repertorier le label
	*i += j + 1;
	return (TOK_LABEL);
}

char	get_tok_newline(t_env *env, char *stream, unsigned int *i)
{
	(void)env;
	if (FCHAR == '\n')
	{
		*i += 1;
		return (TOK_NEWLINE);
	}
	return (0);
}

char	get_tok_comment(t_env *env, char *stream, unsigned int *i)
{
	unsigned int	j;

	(void)env;
	j = 1;
	if (FCHAR != '#')
		return (0);
	while (stream[j] && stream[j] != '\n')
		j++;
	*i += j;
	return (TOK_COMMENT);
}
