/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:15:41 by moguy             #+#    #+#             */
/*   Updated: 2019/10/16 16:53:04 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>


void	aff_env(t_env *env, bool all)
{
	int		i;

	i = -1;
	printf("*******************ENV********************\n\n");
	if (all)
	{
		if (env->nb_players > 0)
			while (++i < (int)env->nb_players)
				aff_player(&env->player[i]);
		if (env->process)
			aff_process(env->process);
		if (env->queue_process)
		{
			printf("****************QUEUE_PROCESS**************\n\n");
			aff_process(env->queue_process);
		}
	}
	printf("*********INFO**********\n\n");
	printf("DUMP = %lld\n", env->dump);
	printf("NB_PLAYER = %u\n", env->nb_players);
	printf("LIVE TOTAL = %u\n\n", env->live_tot);
	i = -1;
	while (++i < (int)env->nb_players)
		printf("LIVE PLAYER %d = %u\n", i, env->nb_lives[i]);
	printf("\nCYCLE_TO_DIE = %d\n\n", env->cycle_to_die);
	printf("*******************ARENA*****************\n\n");
	printf("%s\n\n", env->arena);
}

void	aff_player(t_player *player)
{
	printf("*******************PLAYER*****************\n\n");
	printf("ID = %lld\n", player->id);
	printf("********COMMENT********\n\n");
	printf("%s\n\n", player->comment);
	printf("*******PROG_NAME*******\n\n");
	printf("%s\n\n", player->prog_name);
	printf("********CHAMPION*******\n\n");
	printf("%s\n\n", player->champ);
	printf("*********INFO**********\n\n");
	printf("MAGIC = %x\n", player->magic);
	printf("SIZE = %u\n", player->siz);
	printf("FIRST_PC = %u\n", player->first_pc);
	printf("WAIT_CYCLE = %d\n", player->cycle_to_process);
	printf("DEAD = %s\n", (!player->dead) ? "NO": "YES");
}

void	aff_process(t_process *process)
{
	t_process *tmp;
	int		i;

	i = 0;
	tmp = process;
	while (tmp->next != NULL)
	{
		printf("******************PROCESS******************\n\n");
		printf("Process %d\n\n", i);
		printf("PC = %u\n", tmp->pc);
		printf("carry = %d\n", tmp->carry);
		printf("prev = %p\n", (void*)tmp->prev);
		printf("next = %p\n\n", (void*)tmp->next);
		printf("R[0] = id = %d\n\n", tmp->r[0]);
		tmp = tmp->next;
		i++;
	}
	printf("******************LAST_PROCESS OR ONLY_PROCESS******************\n\n");
	printf("Process %d\n\n", i);
	printf("PC = %u\n", tmp->pc);
	printf("carry = %d\n", tmp->carry);
	printf("prev = %p\n", (void*)tmp->prev);
	printf("next = %p\n\n", (void*)tmp->next);
	printf("R[0] = id = %d\n\n", tmp->r[0]);
}
