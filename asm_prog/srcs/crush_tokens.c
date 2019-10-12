/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crush_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:27:31 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/12 20:32:45 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// Virer les commentaires
// Virer les \n consecutifs

int		crush_tokens(t_env *env)
{
	t_token			*tmp;
	t_token			*tmp2;

	tmp = env->tokens;
	while (tmp)
	{
		if (get_comment(tmp) || get_newline(tmp))
		{
			tmp->prev->next = tmp->next;
			free(tmp);
			tmp = env->tokens;
			continue ;
		}
		tmp = tmp->next;
	}
	return (0);
}
