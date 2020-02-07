/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 01:17:03 by moguy             #+#    #+#             */
/*   Updated: 2020/02/07 08:05:10 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void				buf_char(t_buf arg, char *buf, int *j)
{
	buf[*j] = arg.c;
	*j += 1;
}

static inline void	help_int(char *buf, char *tmp, int i, int k)
{
	while (--k >= 0)
	{
		buf[i] = tmp[k];
		i++;
	}
}

void				buf_int(t_buf arg, char *buf, int *j)
{	
	int				i;
	int				k;
	int				n;
	char			tmp[10];
	static char		dt[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

	k = 0;
	n = arg.n;
	i = *j;
	if (n == -2147483648)
	{
		ft_strcpy(&buf[i], "-2147483648");
		i += 11;
		return ;
	}
	if (n < 0 && (n = -n))
		buf[i++] = '-';
	while (n > 9)
	{
		tmp[k++] = dt[n % 10];
		n /= 10;
	}
	tmp[k++] = dt[n % 10];
	*j = i + k;
	help_int(&buf[0], &tmp[0], i, k);
}

void				buf_uint(t_buf arg, char *buf, int *j)
{
	int				i;
	int				k;
	unsigned int	n;
	char			tmp[10];
	static char		deci_tab[10] = {'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9'};

	k = 0;
	i = *j;
	n = arg.u;
	while (n > 9)
	{
		tmp[k] = deci_tab[n % 10];
		n /= 10;
		k++;
	}
	tmp[k++] = deci_tab[n % 10];
	*j = i + k;
	help_int(&buf[0], &tmp[0], i, k);
}

static inline char	hex_convert_char(unsigned int x, int unit)
{
	unsigned int	n;
	static char		hex_tab[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

	n = x;
	if (unit > 0)
		n /= 16;
	if (unit > 1)
		n /= 16;
	if (unit > 2)
		n /= 16;
	n = n % 16;
	return (hex_tab[n]);
}

void				buf_hex(t_buf arg, char *buf, int *j)
{
	int				i;

	i = *j;
	buf[i] = '0';
	buf[i + 1] = 'x';
	buf[i + 2] = '0';
	buf[i + 3] = '0';
	buf[i + 4] = '0';
	buf[i + 5] = '0';
	if (arg.x > 0)
		buf[i + 5] = hex_convert_char(arg.x, 0);
	if (arg.x >= 16)
		buf[i + 4] = hex_convert_char(arg.x, 1);
	if (arg.x >= 256)
		buf[i + 3] = hex_convert_char(arg.x, 2);
	if (arg.x >= 4096)
		buf[i + 2] = hex_convert_char(arg.x, 3);
	i += 6;
	*j = i;
}

void				buf_str(t_buf arg, char *buf, int *j)
{
	int				i;
	int				k;

	k = 0;
	i = *j;
	while (arg.str[k])
	{
		buf[i] = arg.str[k];
		k++;
		i++;
	}
	*j = i;
}

void				buffer_cor(t_buf arg, int path, bool flush)
{
	static int		i = 0;
	static char		buf[SHRT_MAX];

	if (path > -1)
		g_buf_tab[path].f(arg, &buf[0], &i);
	if (flush || i > SHRT_MAX - 100 )
	{
		write(1, &buf[0], (size_t)i);
		i = 0;
	}
}
