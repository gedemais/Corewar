/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 20:23:00 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/09 16:09:28 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		lexerr(char *ptr, unsigned int line, unsigned int col, char *msg)
{
	char			*nb_line;
	char			*nb_col;
	unsigned int	i;

	i = 0;
	if (!(nb_line = ft_itoa((int)line))
		|| !(nb_col = ft_itoa((int)col)))
		return (1);
	ft_putstr_fd("Invalid syntax line ", 2);
	ft_putstr_fd(nb_line, 2);
	free(nb_line);
	ft_putstr_fd(" col ", 2);
	ft_putstr_fd(nb_col, 2);
	free(nb_col);
	ft_putendl_fd(" :", 2);
	if (line == 0)
		return (1);
	i -= col;
	while (ptr[++i] && ptr[i] != '\n')
		ft_putchar_fd(ptr[i], 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd(msg, 2);
	return (1);
}

int		unex_token_err(char *line, unsigned int nline, unsigned int col)
{
	char			*nb_line;
	char			*nb_col;
	int				i;

	i = 0;
	if (!(nb_line = ft_itoa((int)nline))
		|| !(nb_col = ft_itoa((int)col)))
		return (1);
	ft_putstr_fd("Unexpected token line ", 2);
	ft_putstr_fd(nb_line, 2);
	ft_putstr_fd(" col ", 2);
	ft_putstr_fd(nb_col, 2);
	free(nb_line);
	free(nb_col);
	ft_putendl_fd(":", 2);
	i -= col;
	ft_putstr_fd(L_GREEN, 2);
	while (line[++i] && line[i] != '\n')
	{
		ft_putstr_fd(i == 0 ? RED : NULL, 2);
		ft_putchar_fd(line[i], 2);
		ft_putstr_fd((i > 0 && ft_is_whitespace(line[i])) ? STOP : NULL, 2);
	}
	ft_putchar_fd('\n', 2);
	return (1);
}
