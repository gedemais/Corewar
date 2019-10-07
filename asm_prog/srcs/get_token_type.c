#include "asm.h"

static inline int	mono_char(char c, unsigned int *line)
{
	if (c == '\n')
	{
		*line += 1;
		return (TOK_NEWLINE);
	}
	else if (c == '%')
		return (TOK_PERCENT);
	else if (c == ':')
		return (TOK_COLON);
	return (0);
}

static inline int	get_register(char *stream, unsigned int *j)
{
	unsigned int	i;

	i = 1;
	if (stream[i] != 'r' || !ft_isdigit(stream[i + 1]))
		return (0);
	if (ft_atoi(&stream[1]) >= REG_NUMBER)
		return (0);
	while (ft_isdigit(stream[i]))
		i++;
	*j += i;
	return (TOK_REG);
}

int	get_token_type(char *stream, unsigned int *j, unsigned int *line)
{
	unsigned int	i;
	int		ret;

	ret = 0;
	i = *j;
	if ((ret = mono_char(stream[i], line)) && ((*j) += 1))
		return (ret);
	else if ((ret = get_register(&stream[i], j)))
		return (ret);
	return (0);
}
