/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:53:41 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/29 17:15:58 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				read_big_endian(t_env *env, int fd, bool magic)
{
	ssize_t		ret;
	int			reverse;

	if ((ret = read(fd, (void*)&reverse, 4)) < 1)
		return (1);
	reverse = rev_bits(reverse);
	if (magic)
	{
		env->player[env->nb_pl].magic = (uint32_t)reverse;
		if (env->player[env->nb_pl].magic != COREWAR_EXEC_MAGIC)
			return (1);
	}
	else
	{
		env->player[env->nb_pl].size = (uint32_t)reverse;
		if (env->player[env->nb_pl].size > CHAMP_MAX_SIZE)
			return (1);
	}
	return (0);
}

int				loader(t_env *env, char *arg, unsigned int *j)
{
	char			*file_name;
	int				fd;
	ssize_t			ret;

	if (!(file_name = ft_strndup(&arg[*j], (int)get_name_len(&arg[*j]))))
		return (error(MALLOC_ERR, NULL, NULL));
	if ((fd = open(file_name, O_RDONLY)) < 1)
		return (error(BAD_FILE, USAGE, file_name));
	ft_strdel(&file_name);
	if (read_big_endian(env, fd, true))
		return (error(BAD_FILE, USAGE, NULL));
	if ((ret = read(fd, &env->player[env->nb_pl].name[0], PROG_NAME_LENGTH)) < 1
		|| (ret = read(fd, &env->player[env->nb_pl].pad[0][0], 4)) < 1
		|| env->player[env->nb_pl].pad[0] != 0)
		return (error(BAD_FILE, USAGE, NULL));
	if (read_big_endian(env, fd, false))
		return (error(BAD_FILE, USAGE, NULL));
	if ((ret = read(fd, &env->player[env->nb_pl].com[0], COMMENT_LENGTH)) < 1
		|| (ret = read(fd, &env->player[env->nb_pl].pad[1][0], 4)) < 1
		|| env->player[env->nb_pl].pad[1][0] != 0
		|| (ret = read(fd, &env->player[env->nb_pl].champ[0],
				env->player[env->nb_pl].size + 1)) < 1
		|| ret != env->player[env->nb_pl].size)
		return (error(BAD_FILE, USAGE, NULL));
	return (0);
}
