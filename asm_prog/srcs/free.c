/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:38:04 by gedemais          #+#    #+#             */
/*   Updated: 2019/11/07 21:49:16 by demaisonc        ###   ########.fr       */
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
	{
		token_free_lst(env->tokens);
		env->tokens = NULL;
	}
	if (env->lexemes)
		free(env->lexemes);
	if (env->labels)
		free(env->labels);
	if (env->bin_name)
		free(env->bin_name);
	return (0);
}
