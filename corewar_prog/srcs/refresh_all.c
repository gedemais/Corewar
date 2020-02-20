/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 01:22:11 by moguy             #+#    #+#             */
/*   Updated: 2020/02/17 01:33:42 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	refresh_all(t_env *env)
{
	clear();
	write_border(env);
	write_info(env);
	write_arena(env);
	refresh();
}
