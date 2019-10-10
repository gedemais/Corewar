#include "asm.h"

static inline bool	is_label(t_env *env, char *stream, size_t size)
{
	(void)env;
	(void)stream;
	(void)size;
	return (true);
}

char	get_tok_p_name(t_env *env, char *stream, unsigned int *i)
{
	size_t	prop_len;

	(void)env;
	prop_len = ft_strlen(NAME_CMD_STRING);
	if (FCHAR != '.')
		return (0);
	if (!ft_strncmp(NAME_CMD_STRING, stream, prop_len))
	{
		*i += prop_len;
		return (TOK_P_NAME);
	}
	return (0);
}

char	get_tok_p_com(t_env *env, char *stream, unsigned int *i)
{
	size_t	prop_len;

	(void)env;
	prop_len = ft_strlen(COMMENT_CMD_STRING);
	if (FCHAR != '.')
		return (0);
	if (!ft_strncmp(COMMENT_CMD_STRING, stream, prop_len))
	{
		*i += prop_len;
		return (TOK_P_COM);
	}
	return (0);
}

char	get_tok_string(t_env *env, char *stream, unsigned int *i)
{
	unsigned int	j;

	(void)env;
	j = 1;
	if (FCHAR != '"')
		return (0);
	while (stream[j] && stream[j] != '"' && stream[j] != '\n')
		j++;
	if (!stream[j] || stream[j] != '"')
		return (0);
	*i += j + 1;
	return (TOK_STRING);
}

char	get_tok_reg(t_env *env, char *stream, unsigned int *i)
{
	unsigned int	j;

	(void)env;
	j = 1;
	if (FCHAR != 'r')
		return (0);
	while (stream[j] && ft_isdigit(stream[j]))
		j++;
	if (j == 1 || j > 3 || ft_atoi(&stream[1]) > REG_NUMBER)
		return (0);
	*i += j;
	return (TOK_REG);
}

char	get_tok_number(t_env *env, char *stream, unsigned int *i)
{
	unsigned int	j;

	(void)env;
	j = 0;
	if (!ft_isdigit(FCHAR) && FCHAR != '-' && FCHAR != '+')
		return (0);
	while (stream[j] && ft_isdigit(stream[j]))
		j++;
	if (j == 0 || ft_atoi(&stream[1]) >= REG_NUMBER)
		return (0);
	*i += j;
	return (TOK_NUMBER);
}

char	get_tok_lnumber(t_env *env, char *stream, unsigned int *i)
{
	unsigned int	j;

	(void)env;
	j = 1;
	if (FCHAR != '%')
		return (0);
	while (stream[j] && ft_isdigit(stream[j]))
		j++;
	if (j == 1)
		return (0);
	*i += j;
	return (TOK_LNUMBER);
}

char	get_tok_dlaba(t_env *env, char *stream, unsigned int *i)
{
	size_t	size;

	size = 2;
	if (FCHAR != '%' || stream[1] != ':')
		return (0);
	while (stream[size] && (ft_isalnum(stream[size]) || stream[size] == '_'))
		size++;
	if (!is_label(env, &stream[2], size))
		return (0);
	*i += size;
	return (TOK_DLABA);
}

char	get_tok_indlaba(t_env *env, char *stream, unsigned int *i)
{
	size_t	size;

	size = 1;
	if (FCHAR != ':')
		return (0);
	while (stream[size] && ft_isalnum(stream[size]))
		size++;
	if (!is_label(env, &stream[1], size))
		return (0);
	*i += size + 1;
	return (TOK_INDLABA);
}

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