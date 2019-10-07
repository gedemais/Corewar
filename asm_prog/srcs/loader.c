/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:53:41 by gedemais          #+#    #+#             */
/*   Updated: 2019/10/07 19:43:35 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline void	debug(t_env *env)
{
	fprintf((FILE*)stderr, "File :\n%s\n", env->file);
}

static inline char	*strrealloc(char *s, unsigned int size)
{
	char	*new;

	if (!(new = ft_strnew(size)))
	{
		free(s);
		return (NULL);
	}
	new = ft_strcpy(new, s);
	free(s);
	return (new);
}

static inline char	*buffer_join(char *dst, const char *src, unsigned int start)
{
	unsigned int	i;

	i = 0;
	while (src[i])
	{
		dst[i + start] = src[i];
		i++;
	}
	dst[i + start] = '\0';
	return (dst);
}

static inline char	*read_file(int fd)
{
	char			buff[BUFF_READ + 1];
	char			*dest;
	int				ret;
	unsigned int	size[2];

	size[0] = BUFF_READ;
	size[1] = 0;
	if (fd == -1 || !(dest = ft_strnew(BUFF_READ)))
		return (NULL);
	while ((ret = (int)read(fd, buff, BUFF_READ)) > 0)
	{
		size[1] += (unsigned int)ret;
		buff[ret] = '\0';
		if (size[1] >= size[0] && (size[0] *= 2) > 0
			&& !(dest = strrealloc(dest, size[0])))
			return (NULL);
		dest = buffer_join(dest, buff, size[1] - (unsigned int)ret);
	}
	if (ret == -1)
	{
		free(dest);
		return (NULL);
	}
	return (dest);
}

int		loader(t_env *env, char *file_name)
{
	int		fd;

	if ((fd = open(file_name, O_RDONLY) == -1))
	{
		ft_putendl_fd(FILE_ERR_MSG, 2);
		return (-1);
	}
	if (!(env->file = read_file(open(file_name, O_RDONLY)))
		|| !env->file[0])
		return (-1);
	if (DEBUG_MODE)
		debug(env);
	return (0);
}
