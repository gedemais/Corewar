/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:53:41 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/17 15:48:02 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				error(char *error_msg, char *file)
{
	if (file)
		ft_strdel(&file);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	return (1);
}

int				check_id(t_env *env)
{
	long long int	tab[4];
	unsigned int	i;
	unsigned int	j;

	i = 0;
	ft_memset((void*)&tab[0], 0, 4);
	while (i < env->nb_players)
	{
		if (env->player[i].id > env->nb_players)
			return (1);
		tab[i] = env->player[i].id;
		i++;
	}
	i = 0;
	while (tab[i] && i < 4)
	{
		j = i + 1;
		while (tab[j] && j < 4)
		{
			if (tab[i] == tab[j] && tab[i] != 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int				reverse_bytes(t_player *player)
{
	(void)player;
	return (0);
}

long long int	find_id(t_env *env)
{
	unsigned int	i;
	long long int	ret;

	i = 0;
	ret = 1;
	while (i < env->nb_players)
	{
		if (ret == env->player[i].id)
		{
			i = 0;
			ret++;
		}
		else
			i++;
	}
	return (ret);
}

int				loader(t_env *env, t_player *player, char *arg,
																		int len)
{
	char			*file_name;
	int				fd;
	long			ret;

	if (!(file_name = ft_strndup(arg, len)))
		return (error(MALLOC_ERR, NULL));
	if ((fd = open(file_name, O_RDONLY)) < 1)
		return (error(FILE_ERR_MSG, file_name));
	if ((ret = read(fd, (void*)&player->magic, 4)) < 1 || player->magic != 0xf383ea00)
		return (error(FILE_ERR_MSG, file_name));
	if ((ret = read(fd, &player->prog_name[0], PROG_NAME_LENGTH)) < 1
		|| (ret = read(fd, &player->pad, 4)) < 1 || player->pad != 0)
		return (error(FILE_ERR_MSG, file_name));
	if ((ret = read(fd, &player->siz_rev[0], 4)) < 1 
			&& (ft_strrev(&player->siz_rev[0])) && 
		return (error(FILE_ERR_MSG, file_name));
//	reverse_bytes(player);
	if ((ret = read(fd, &player->comment[0], COMMENT_LENGTH)) < 1
			|| (ret = read(fd, &player->pad, 4)) < 1 || player->pad != 0
			|| (ret = read(fd, &player->champ[0], player->siz)) < 1)
	{
		ft_putnbr((int)ret);
		return (error(FILE_ERR_MSG, file_name));
	}
	ft_strdel(&file_name);
	if (player->id == 0)
		player->id = find_id(env);
	check_id(env);
	env->nb_players++;
	return (0);
}
