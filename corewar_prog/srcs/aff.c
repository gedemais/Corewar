/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:15:41 by moguy             #+#    #+#             */
/*   Updated: 2019/10/31 15:50:11 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>


void	aff_env(t_env *env, bool all)
{
	int		i;

	printf("*******************ENV********************\n\n");
	printf("*********INFO**********\n\n");
	printf("NB_PLAYER = %u\n", env->nb_pl);
	printf("CURR_LIVES = %u\n\n", env->curr_lives);
	printf("\nCYCLE_CURR = %d\n\n", env->cycle_curr);
	printf("\nCYCLE_TOT = %d\n\n", env->cycle_tot);
	printf("\nCYCLE_TO_DIE = %d\n\n", env->cycle_to_die);
	i = -1;
	if (env->nb_pl > 0)
	{
		while (++i < (int)env->nb_pl)
		{
			aff_player(&env->player[i]);
			printf("LIVE PLAYER %d = %u\n", i, env->live_pl[i]);
		}
	}
	if (all)
	{
		if (env->process)
			aff_process(env->process, true);
		printf("*******************ARENA*****************\n\n");
		dump(env);
	}
	printf("*****************************************************************************************************************\n\n");
}

void	aff_player(t_player *player)
{
	printf("*******************PLAYER*****************\n\n");
	printf("ID = %d\n", player->id);
	printf("********COMMENT********\n\n");
	printf("%s\n\n", player->com);
	printf("*******PROG_NAME*******\n\n");
	printf("%s\n\n", player->name);
	printf("********CHAMPION*******\n\n");
	printf("%s\n\n", player->champ);
	printf("*********INFO**********\n\n");
	printf("MAGIC = %#.8x\n", player->magic);
	printf("SIZE = %u\n", player->size);
}

static inline void	aff_instruct(t_process *p)
{
	printf("******************INSTRUCTION******************\n\n");
	printf("OP_CODE = %u\n", (unsigned int)p->instruct.op);
	printf ("Types = %u,  %u,  %u.\n", p->instruct.args[0].type,
		p->instruct.args[1].type, p->instruct.args[2].type);
	printf ("REG = %u,  %u,  %u.\n", p->instruct.args[0].id,
		p->instruct.args[1].id, p->instruct.args[2].id);
	printf ("ARG= %u,  %u,  %u.\n", p->instruct.args[0].arg,
		p->instruct.args[1].arg, p->instruct.args[2].arg);
}

void	aff_process(t_process *process, bool all)
{
	t_process	*tmp;

	if (!process)
	{
		printf("tmp = NULL\n");
		return ;
	}
	tmp = process;
	while (tmp)
	{
		printf("******************PROCESS******************\n\n");
		printf("id = %d\n\n", tmp->r[0]);
		printf("PC = %u\n", tmp->pc);
		printf("Wait cycle = %d\n", tmp->cycle_to_exec);
		printf("alive = %d\n", tmp->alive);
		printf("carry = %d\n", tmp->carry);
		printf("next = %p\n\n", (void*)tmp->next);
		printf("***************REGISTER****************\n\n");
		printf("%d  %d  %d  %d\n%d  %d  %d  %d\n%d  %d  %d  %d\n%d  %d  %d  %d\n\n",
			tmp->r[0], tmp->r[1], tmp->r[2], tmp->r[3],
			tmp->r[4], tmp->r[5], tmp->r[6], tmp->r[7],
			tmp->r[8], tmp->r[9], tmp->r[10], tmp->r[11],
			tmp->r[12], tmp->r[13], tmp->r[14], tmp->r[15]);
		aff_instruct(tmp);
		if (tmp->next && all)
			tmp = tmp->next;
		else
			tmp = NULL;
	}
}
