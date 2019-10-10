#include "asm.h"

char	get_tok_p_name(char *stream, unsigned int *i)
{
	size_t	prop_len;

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

char	get_tok_p_com(char *stream, unsigned int *i)
{
	size_t	prop_len;

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

char	get_tok_string(char *stream, unsigned int *i)
{
	unsigned int	j;

	j = 0;
	if (FCHAR != '"')
		return (0);
	while (stream[j] && stream[j] != '"' && stream[j] != '\n')
		j++;
	if (stream[j] && stream[j] != '"')
		return (0);
	*i += j;
	return (TOK_STRING);
}

char	get_tok_reg(char *stream, unsigned int *i)
{
	unsigned int	j;

	j = 1;
	if (FCHAR != 'r')
		return (0);
	while (ft_isdigit(stream[j]))
		j++;
	if (j == 1 || j > 3 || ft_atoi(&stream[1]) >= REG_NUMBER)
		return (0);
	return (TOK_REG);
}

char	get_tok_number(char *stream, unsigned int *i)
{
	if (!ft_isdigit(FCHAR) && FCHAR != '-' && FCHAR != '+')
		return (0);
	if (FCHAR == '+' || FCHAR == '-')
	{
		if (ft_atoi(stream) != 0)
			return (TOK_NUMBER);
	}
	else
		return (TOK_NUMBER);
}

char	get_tok_(char *stream, unsigned int *i)
{
	return (0);
}

char	get_tok_(char *stream, unsigned int *i)
{
	return (0);
}

char	get_tok_(char *stream, unsigned int *i)
{
	return (0);
}

char	get_tok_(char *stream, unsigned int *i)
{
	return (0);
}

char	get_tok_(char *stream, unsigned int *i)
{
	return (0);
}

char	get_tok_(char *stream, unsigned int *i)
{
	return (0);
}




