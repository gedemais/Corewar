/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:53:41 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/15 13:20:43 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		error(char *error_msg, char *file)
{
	if (file)
		ft_strdel(&file);
	ft_putendl_fd(error_msg, STDERR_FILENO);
	return (1);
}

int		reverse_bytes(t_player *player)
{
	return (0);
}

int		loader(t_env *env, t_player *player, char *arg, int len)
{
	char		*file_name;
	int			fd;
	int			ret;

	if (!(file_name = ft_strndup(arg, len)))
		return (error(MALLOC_ERR, NULL));
	if ((fd = open(file_name, O_RDONLY)) < 1)
		return (error(FILE_ERR_MSG, file_name))
	if ((ret = read(fd, player->magic, 4)) < 1 || player->magic != 0xf383ea00)
		return (error(FILE_ERR_MSG, file_name))
	if ((ret = read(fd, &player->prog_name[0], PROG_NAME_LENGTH)) < 1
		|| (ret = read(fd, &player->pad, 4)) < 1 || player->pad != 0)
		return (error(FILE_ERR_MSG, file_name));
	if ((ret = read(fd, &player->siz, 4)) < 1 || player->siz == CHAMP_MAX_SIZE)
		return (error(FILE_ERR_MSG, file_name));
	if ((ret = read(fd, &player->comment[0], COMMENT_LENGTH)) < 1
			|| (ret = read(fd, &player->pad, 4)) < 1 || player->pad != 0
			|| (ret = read(fd, &player->champ[0], player->siz)) < 1)
		return (error(FILE_ERR_MSG, file_name));
//	reverse_bytes(player);
	ft_strdel(&file_name);
	if (player->id == 0)
		player->id = env->nb_players + 1;
	env->nb_players++;
	return (0);
}
