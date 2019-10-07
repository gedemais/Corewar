/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:45:10 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/08 00:53:43 by demaisonc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline int	unex_token_err(char *line, unsigned int nline)
{
	char		*nb_line;
	unsigned int	i;

	i = 0;
	if (!(nb_line = ft_itoa((int)nline)))
		return (-1);
	ft_putstr_fd("Unexpected token line", 2);
	ft_putendl_fd(nb_line, 2);
	ft_putstr_fd(": ", 2);
	free(nb_line);
	while (line[i] && line[i] != '\n')
	{
		ft_putchar_fd(line[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	return (0);
}

int		tokenizer(t_env *env)
{
	unsigned int	i;
	unsigned int	t;
	unsigned int	line;

	i = 0;
	t = 0;
	line = 0;
	if (!(env->tokens = (t_token*)malloc(sizeof(t_token) * NB_TOKENS)))
		return (-1);
	while (env->file[i])
	{
		if (get_token_type(&env->file[i], &i, &line) &&
			!unex_token_err(&env->file[i], line))
			return (-1);
		t++;
	}
	return (0);
}
