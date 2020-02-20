/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 04:52:20 by moguy             #+#    #+#             */
/*   Updated: 2020/02/20 04:15:11 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline int	write_stealth(t_env *env, int x, int y, int color)
{
	mvwaddch(stdscr, y, x, 'f');
	if (x + 1 < env->xmax)
		mvwaddch(stdscr, y, x + 1, 'f');
	attroff((unsigned int)COLOR_PAIR(color) | A_BOLD);
	if (x + 2 < env->xmax)
		mvwaddch(stdscr, y, x + 2, ' ');
	return (1);
}

static inline void	write_color(t_env *env, int x, int y, int i)
{
	int		color;

	color = env->arena[i].id;
	if (color < 0)
		color = -color;
	if (env->arena[i].living-- > 0 && color != 0)
	{
		color += 20;
		attron(A_BOLD);
	}
	else if (env->arena[i].used == true && env->process)
		color += 10;
	else if (env->arena[i].recent > 0 && color != 0)
		attron(A_BOLD);
	env->arena[i].recent--;
	attron(COLOR_PAIR(color));
	if (env->opt[O_STEALTH])
		if (write_stealth(env, x, y, color))
			return ;
	mvwaddch(stdscr, y, x, hex_tab((env->arena[i].value >> 4) & 0xf));
	if (x + 1 < env->xmax)
		mvwaddch(stdscr, y, x + 1, hex_tab(env->arena[i].value & 0xf));
	attroff((unsigned int)COLOR_PAIR(color) | A_BOLD);
	if (x + 2 < env->xmax)
		mvwaddch(stdscr, y, x + 2, ' ');
}

void				write_arena(t_env *env)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	y = 1;
	while (++y < ARENA_LINES && y < env->ymax)
	{
		x = 3;
		while (x < ARENA_COLS && i < MEM_SIZE && x < env->xmax)
		{
			write_color(env, x, y, i);
			i++;
			x += 3;
		}
	}
}
