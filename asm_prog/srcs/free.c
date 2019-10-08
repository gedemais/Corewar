/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:38:04 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/08 15:57:50 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
/*
static inline char	**free_ctab(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}*/

int		free_env(t_env *env)
{
	if (env->file)
	{
		free(env->file);
		env->file = NULL;
	}
	if (env->tokens)
		token_free_lst(env->tokens);
	return (0);
}
