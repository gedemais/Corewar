/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:38:28 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/08 00:32:45 by demaisonc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline int	asm_compiler(t_env *env, char *file_name)
{
	if (loader(env, file_name)
		|| tokenizer(env))
		return (-1);
	return (0);
}

int					main(int argc, char **argv)
{
	t_env	env;

	if (argc != 2)
	{
		ft_putendl_fd(USAGE, 2);
		return (1);
	}
	else if (asm_compiler(&env, argv[1]) != 0)
	{
		free_env(&env);
		return (1);
	}
	free_env(&env);
	return (0);
}
