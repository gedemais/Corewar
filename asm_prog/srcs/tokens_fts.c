#include "asm.h"

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
	while (stream[j] && (ft_isdigit(stream[j]) || stream[j] == '-' || stream[j] == '+'))
		j++;
	if (j == 0)
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
	if (!is_label(env, &stream[2]))
		return (-1);
	*i += size;
	return (TOK_DLABA);
}

char	get_tok_indlaba(t_env *env, char *stream, unsigned int *i)
{
	size_t	size;

	size = 1;
	if (FCHAR != ':')
		return (0);
	while (stream[size] && (ft_isalnum(stream[size]) || stream[size] == '_'))
		size++;
	if (size == 1)
		return (0);
	if (!is_label(env, &stream[1]))
		return (0);
	*i += size + 1;
	return (TOK_INDLABA);
}
