/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:53:41 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/13 16:57:37 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		loader(t_env *env, char *arg, int len)
{
	int		fd;
	int		ret;
	char	*file_name;

	if (!(file_name = ft_strndup(arg, len)))
		return (1);
	if ((fd = open(file_name, O_RDONLY)) <= 0)
	{
		ft_strdel(&file_name);
		ft_putendl_fd(FILE_ERR_MSG, STDERR_FILENO);
		return (1);
	}
	if ((ret = (int)read(fd, env->files[env->nb_players],
					CHAMP_MAX_SIZE + 1)) > CHAMP_MAX_SIZE
			|| !env->files[env->nb_players][0])
	{
		ft_strdel(&file_name);
		ft_putendl_fd(FILE_ERR_MSG, STDERR_FILENO);
		return (1);
	}
	ft_strdel(&file_name);
	if (env->player[env->nb_players].id == 0)
		env->player[env->nb_players].id = env->nb_players;
	env->nb_players++;
	return (0);
}
