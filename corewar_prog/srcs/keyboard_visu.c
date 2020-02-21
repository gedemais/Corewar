/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_visu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:18:59 by moguy             #+#    #+#             */
/*   Updated: 2020/02/21 01:46:30 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline int	help_pause(t_env *env, int key_input)
{
	if (key_input == 45 && env->ncurses_speed < 250000)
		env->ncurses_speed += 2000;
	else if (key_input == 43 && env->ncurses_speed > 0)
		env->ncurses_speed -= 2000;
	else if (key_input == 113 || key_input == 27 || key_input == 81)
	{
		clear();
		refresh();
		endwin();
		return (1);
	}
	else if (key_input == 's' && env->pause)
	{
		env->onetime = true;
		return (-1);
	}
	if (key_input == 45 || key_input == 43 || !env->process)
	{
		write_info(env);
		refresh();
	}
	return (0);
}

int					pause_loop(t_env *env)
{
	int		key_input;

	while (env->pause || env->cycle_to_die <= 0)
	{
		timeout(-1);
		key_input = getch();
		if (key_input == 410)
			refresh_all(env);
		if (key_input == 32)
		{
			write_info(env);
			refresh();
			env->pause = false;
			return (0);
		}
		if ((key_input = help_pause(env, key_input)) == 1)
			return (1);
		else if (key_input == -1)
			return (0);
	}
	return (0);
}

int					keyboard_visu(t_env *env)
{
	int		key_input;

	timeout(1);
	key_input = getch();
	if (key_input == 32)
	{
		env->pause = true;
		write_info(env);
		refresh();
		if (pause_loop(env))
			return (1);
	}
	key_input = help_pause(env, key_input);
	if (key_input == 1)
		return (1);
	return (0);
}
