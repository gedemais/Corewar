/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:38:28 by gedemais          #+#    #+#             */
/*   Updated: 2019/12/30 22:07:03 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline int	asm_compiler(t_env *env, char *file_name)
{
	if (loader(env, file_name) != 0
		|| tokenizer(env) != 0
		|| lexer(env) != 0)
		return (-1);
	if (write_bytecode(env) != 0)
		return (-1);
	return (0);
}

int					main(int argc, char **argv)
{
	t_env	env;

	ft_memset(&env, 0, sizeof(t_env));
	if (argc != 2)
	{
		ft_putendl_fd(USAGE, 2);
		if (LEAKS)
			system("leaks asm");
		return (1);
	}
	else if (asm_compiler(&env, argv[1]) != 0)
	{
		free_env(&env);
		if (LEAKS)
			system("leaks asm");
		return (1);
	}
	free_env(&env);
	if (LEAKS)
		system("leaks asm");
	return (0);
}
