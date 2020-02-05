/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:07:09 by moguy             #+#    #+#             */
/*   Updated: 2019/10/17 16:40:38 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdio.h>

void	test_lst(void)
{
	t_env		env;
	t_process	*beginning;
	t_process	*process;
	t_process	*process2;
	
	ft_memset(&env, 0, sizeof(t_env));
	env.player[0].id = 53;
	env.player[1].id = 4;
	env.player[2].id = 58967;
	env.player[3].id = 147258369;
	beginning = new_lst(&env, 4, 3072);
	process2 = beginning;
	printf("********NEW_PROCESS********\n\n");
	aff_process(beginning);
	beginning = push_lst(&env, beginning, 3, 2048);
	printf("********ONE_PUSH********\n\n");
	aff_process(beginning);
	process = push_lst(&env, beginning, 1, 0);
	beginning = process;
	beginning = push_lst(&env, beginning, 2, 1024);
	printf("********THREE_PUSH********\n\n");
	aff_process(beginning);
	pop_lst(process, process, NULL);
	printf("********ONE_POP********\n\n");
	aff_process(beginning);
	pop_lst(process2, process2, NULL);
	printf("********TWO_POP********\n\n");
	aff_process(beginning);
	while (beginning->next)
	{
		process = beginning;
		beginning = beginning->next;
		if (process)
		{
			if (process->r)
			{
				free(process->r);
				process->r = NULL;
			}
			free(process);
			process = NULL;
		}
	}
	if (beginning)
	{
		if (beginning->r)
		{
			free(beginning->r);
			beginning->r = NULL;	
		}
		beginning = NULL;
		free(beginning);
	}
	process2 = NULL;
}

void	test_get_opt_champ_loader(char *arg)
{
	t_env	env;

	ft_memset(&env, 0, sizeof(t_env));
	if (arg)
		get_opt_champ(&env, arg);
	else
		get_opt_champ(&env, "-dump 154 toto.cor -n 4 helltrain.cor -n 1 ex.cor turtle.cor");
	aff_env(&env, 1);
}
/*
void	test_convert_instruction(void)
{
	int		ret;
	void	*p;

	ret = hex_convert('0', 'x', 'f', 'f');
	printf("********CONVERT_INSTRUCTION********\n\n");
	printf("HEX_CONVERT 0xff = %d = %x\n\n", ret, ret);
	ret = nb_arg(0);
	printf("NB_ARG 1 = %d\n\n", ret);
	ret = nb_arg(5);
	printf("NB_ARG 3 = %d\n\n", ret);
	ret = nb_arg(15);
	printf("NB_ARG 1 = %d\n\n", ret);
	ret = carry_flag(0);
	printf("CARRY_FLAG 0 = %d\n\n", ret);
	ret = carry_flag(5);
	printf("CARRY_FLAG 1 = %d\n\n", ret);
	ret = carry_flag(15);
	printf("CARRY_FLAG 0 = %d\n\n", ret);
	ret = encoding_byte(0);
	printf("ENCODING_BYTE 0 = %d\n\n", ret);
	ret = encoding_byte(5);
	printf("ENCODING_BYTE 1 = %d\n\n", ret);
	ret = encoding_byte(15);
	printf("ENCODING_BYTE 1 = %d\n\n", ret);
	p = convert_instruction(0);
	printf("ADRESSE DE LA FONCTION LIVE = %p\n\n", (void*)&live);
	printf("TAB_INSTRUCTION[0] = %p\n\n", p);

}

void	test_cw_loop(void)
{
}

void	test_system(void)
{
}
*/
int		main(int ac, char **av)
{
	if (ac == 1)
	{
		(void)av;
		test_lst();
		test_get_opt_champ_loader(NULL);
//		test_convert_instruction();
//		test_cw_loop();
//		test_system();
	
	}
	else
		test_get_opt_champ_loader(av[1]);
	return (0);
}
