#include "asm.h"

static inline void	print_cursor(char *line, unsigned int col)
{
	unsigned int	i;

	i = 0;
	ft_putstr_fd(L_RED, 2);
	while (i < col)
	{
		if (ft_is_whitespace(line[i]))
			ft_putchar_fd(line[i], 2);
		else
			ft_putchar_fd(' ', 2);
		i++;
	}
	ft_putchar_fd('^', 2);
	ft_putchar_fd('\n', 2);
}

static inline void	print_line_n_col(unsigned int line, unsigned int col)
{
	char		*nline;
	char		*ncol;

	if (!(nline = ft_itoa((int)line + 1))
		|| !(ncol = ft_itoa((int)col)))
		return ;
	ft_putstr_fd(LINE, 2);
	ft_putstr_fd(nline, 2);
	free(nline);
	ft_putstr_fd(COL, 2);
	ft_putstr_fd(ncol, 2);
	free(ncol);
	ft_putendl_fd(":", 2);
}

int					expected_newline_err(t_token *tok)
{
	char		*nline;

	if (!(nline = ft_itoa(tok->line)))
		return (-1);
	ft_putstr_fd(L_RED, 2);
	ft_putstr_fd(EX_NEWLINE, 2);
	ft_putstr_fd(STOP, 2);
	ft_putstr_fd(LINE, 2);
	ft_putendl_fd(nline, 2);
	free(nline);
	return (0);
}

int					property_error(char *file, t_token *tok)
{
	unsigned int	i;
	unsigned int	tmp;

	i = tok->index;
	ft_putstr_fd(L_RED, 2);
	ft_putstr_fd((tok->type == TOK_P_COM) ? COMMENT_CMD_ERR : NAME_CMD_ERR, 2);
	ft_putstr_fd(STOP, 2);
	ft_putchar_fd(' ', 2);
	print_line_n_col(tok->line, tok->col);
	while (i > 0 && file[i] != '\n')
		i--;
	i++;
	tmp = i;
	while (file[i] != '\n')
	{
		ft_putchar_fd(file[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	print_cursor(&file[tmp], tok->col);
	return (0);
}

int					undefined_label_err(t_env *env, t_tokenizer *tok)
{
	unsigned int	i;

	i = 0;
	ft_putstr_fd(L_RED, 2);
	ft_putstr_fd(UNDEFINED_LABEL, 2);
	ft_putstr_fd(STOP, 2);
	print_line_n_col(tok->line, tok->col);
	while (&env->file[tok->line_start + i] && env->file[tok->line_start + i] != '\n')
	{
		ft_putchar_fd(env->file[tok->line_start + i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	print_cursor(&env->file[tok->line_start], tok->col);
	return (0);
}

int					invalid_syntax_err(t_env *env, t_tokenizer *tok)
{
	unsigned int	j;

	j = 0;
	ft_putstr_fd(L_RED, 2);
	ft_putstr_fd(INVALID_SYNTAX, 2);
	ft_putstr_fd(STOP, 2);
	print_line_n_col(tok->line, tok->col);
	while (env->file[tok->line_start + j]
		&& env->file[tok->line_start + j] != '\n')
	{
		ft_putchar_fd(env->file[tok->line_start + j], 2);
		j++;
	}
	ft_putchar_fd('\n', 2);
	print_cursor(&env->file[tok->line_start], tok->col);
	return (0);
}

static inline int	get_type_str(int id, char *buff)
{
	if (id == TOK_REG)
	{
		ft_strcpy(buff, "reg");
		return (0);
	}
	else if (id == TOK_NUMBER)
	{
		ft_strcpy(buff, "indirect_num");
		return (0);
	}
	else if (id == TOK_LNUMBER)
	{
		ft_strcpy(buff, "direct_num");
		return (0);
	}
	return (1);
}

static inline void	op_usage(int op)
{
	char			type[MAX_TYPE_SIZE];
	unsigned int	i;
	unsigned int	j;

	i = 0;
	ft_putstr_fd(BLUE, 2);
	ft_putstr_fd("Usage : ", 2);
	ft_putstr_fd(L_GREEN, 2);
	ft_putstr_fd(g_opnames[op], 2);
	ft_putchar_fd(' ', 2);
	while (i < 9)
	{
		j = 0;
		while (j < 3 && g_op_args[op][i + j])
		{
			if (get_type_str(g_op_args[op][i + j], &type[0]) != 0)
				return ;
			ft_putstr_fd(&type[0], 2);
			if (g_op_args[op][i + j + 1])
				ft_putstr_fd("|", 2);
			j++;
		}
		if (g_op_args[op][i + 3])
			ft_putstr_fd(", ", 2);
		i += 3;
	}
}

int					invalid_op_parameter(t_token *tok, int op)
{
	char				type[MAX_TYPE_SIZE];
	unsigned int		j;

	j = 0;
	ft_putstr_fd(L_RED, 2);
	ft_putstr_fd(INVALID_OP_PARAM, 2);
	ft_putstr_fd(STOP, 2);
	print_line_n_col(tok->line, tok->col);
	ft_putstr_fd("Incompatible type ", 1);
	get_type_str(tok->type, &type[0]);
	ft_putstr_fd(L_RED, 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd(STOP, 2);
	ft_putstr_fd(" for ", 2);
	ft_putstr_fd(L_GREEN, 2);
	ft_putendl_fd(g_opnames[op], 2);
	ft_putstr_fd(STOP, 2);
	op_usage(op);
	ft_putchar_fd('\n', 2);
	return (1);
}

int					too_few_op_args(t_token *tok, int op)
{
	ft_putstr_fd(L_RED, 2);
	ft_putstr_fd(TOO_FEW_ARGS, 2);
	ft_putstr_fd(L_GREEN, 2);
	ft_putstr_fd(g_opnames[op], 2);
	ft_putstr_fd(STOP, 2);
	ft_putchar_fd(' ', 2);
	print_line_n_col(tok->line, tok->col);
	op_usage(op);
	ft_putchar_fd('\n', 2);
	return (0);
}

int		unknown_properity(char *stream)
{
	unsigned int	i;

	i = 0;
	ft_putstr_fd(L_RED, 2);
	ft_putstr_fd(UNKNOWN_PROPERITY, 2);
	ft_putstr_fd(STOP, 2);
	ft_putstr_fd(": ", 2);
	while (stream[i] && stream[i] != '\n')
		i++;
	write(2, stream, i);
	ft_putchar_fd('\n', 2);
	return (0);
}

int		not_eno_args(t_token *tok, int op)
{
	unsigned int	i;

	i = 0;
	ft_putstr_fd(L_RED, 2);
	ft_putstr_fd(NOT_ENO_ARGS, 2);
	ft_putstr_fd(L_GREEN, 2);
	ft_putstr_fd(g_opnames[op], 2);
	ft_putstr_fd(STOP, 2);
	ft_putchar_fd(' ', 2);
	print_line_n_col(tok->line, tok->col);
	op_usage(op);
	ft_putchar_fd('\n', 2);
	return (1);
}
