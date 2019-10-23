/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:15:41 by moguy             #+#    #+#             */
/*   Updated: 2019/10/23 21:41:26 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>


void	aff_env(t_env *env, bool all)
{
	int		i;

	printf("*******************ENV********************\n\n");
	printf("*********INFO**********\n\n");
	printf("DUMP = %lld\n", env->dump);
	printf("NB_PLAYER = %u\n", env->nb_players);
	printf("LIVE TOTAL = %u\n\n", env->live_tot);
	i = -1;
	if (env->nb_players > 0)
		while (++i < (int)env->nb_players)
			aff_player(&env->player[i]);
	i = -1;
	while (++i < (int)env->nb_players)
		printf("LIVE PLAYER %d = %u\n", i, env->nb_lives[i]);
	printf("\nCYCLE_TO_DIE = %d\n\n", env->cycle_to_die);
	printf("*******************ARENA*****************\n\n");
	printf("%s\n\n", env->arena);
	if (all)
		if (env->process)
			aff_process(env->process);
	printf("*****************************************************************************************************************\n\n");
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
	printf("DEAD = %s\n", (!player->dead) ? "NO": "YES");
}

static inline void	aff_instruct(t_process *p)
{
	printf("******************INSTRUCTION******************\n\n");
	printf("Wait cycle = %d\n", p->instruct.wait_cycle);
	printf("OP_CODE = %c\n", p->instruct.op_code);
	printf ("Types = %hhd,  %hhd,  %hhd.\n", p->instruct.type[0],
		p->instruct.type[1], p->instruct.type[2]);
}

void	aff_process(t_process *process)
{
	t_process	*tmp;
	int			i;

	i = 0;
	tmp = process;
	while (tmp->next != NULL)
	{
		printf("******************PROCESS******************\n\n");
		printf("Process %d\n\n", i);
		printf("PC = %u\n", tmp->pc);
		printf("PCI = %u\n", tmp->pci);
		printf("carry = %d\n", tmp->carry);
		printf("next = %p\n\n", (void*)tmp->next);
		printf("id = %d\n\n", tmp->r[0]);
		printf("***************REGISTER****************\n\n");
		printf("%d  %d  %d  %d\n%d  %d  %d  %d\n%d  %d  %d  %d\n%d  %d  %d  %d\n\n",
			tmp->r[0], tmp->r[1], tmp->r[2], tmp->r[3],
			tmp->r[4], tmp->r[5], tmp->r[6], tmp->r[7],
			tmp->r[8], tmp->r[9], tmp->r[10], tmp->r[11],
			tmp->r[12], tmp->r[13], tmp->r[14], tmp->r[15]);
		aff_instruct(tmp);
		tmp = tmp->next;
		i++;
	}
	printf("******************LAST_PROCESS OR ONLY_PROCESS******************\n\n");
	printf("Process %d\n\n", i);
	printf("PC = %u\n", tmp->pc);
	printf("PCI = %u\n", tmp->pci);
	printf("carry = %d\n", tmp->carry);
	printf("next = %p\n\n", (void*)tmp->next);
	printf("id = %d\n\n", tmp->r[0]);
	printf("%d  %d  %d  %d\n%d  %d  %d  %d\n%d  %d  %d  %d\n%d  %d  %d  %d\n\n",
		tmp->r[0], tmp->r[1], tmp->r[2], tmp->r[3],
		tmp->r[4], tmp->r[5], tmp->r[6], tmp->r[7],
		tmp->r[8], tmp->r[9], tmp->r[10], tmp->r[11],
		tmp->r[12], tmp->r[13], tmp->r[14], tmp->r[15]);
	aff_instruct(tmp);
}
