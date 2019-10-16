/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:48:16 by moguy             #+#    #+#             */
/*   Updated: 2019/10/14 10:29:28 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*• La machine virtuelle se lance de la façon suivante :
> ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...
• -dump nbr_cycles
Au bout de nbr_cycles cycles d’exécution, 
dump la mémoire sur la sortie standard, 
puis quitte la partie. 
La mémoire doit être dumpée au format hexadécimal,
avec 32 octets par ligne.
• -n number
Fixe le numéro du prochain joueur. Si absent, 
le joueur aura le prochain numéro
libre dans l’ordre des paramètres. 
Le dernier joueur aura le premier processus dans
l’ordre d’exécution.
• Les champions ne peuvent pas dépasser CHAMP_MAX_SIZE, sinon c’est une
erreur.*/

static inline int	get_id(t_env *env, char *arg, unsigned int *j)
{
	unsigned int	i;

	i = *j + 1;
	while (arg[i] && ft_is_whitespace(arg[i]))
		i++;
	if ((env->player[env->nb_players].id = ft_atoi(&arg[i])) < 0
			|| env->player[env->nb_players].id > INT_MAX)
		return (error(BAD_NUMBER, NULL));
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	if (arg[i] && !ft_is_whitespace(arg[i]))
		return (1);
	*j = i;
	return (0);
}

static inline int	get_dump(t_env *env, char *arg, unsigned int *j)
{
	unsigned int	i;

	i = *j + 4;
	while (arg[i] && ft_is_whitespace(arg[i]))
		i++;
	if (env->dump != 0 || (env->dump = ft_atoi(&arg[i])) < 1
			|| env->dump > INT_MAX)
		return (error(BAD_NUMBER, NULL));
	while (arg[i] && !ft_is_whitespace(arg[i]))
		i++;
	*j = i;
	return (0);
}

static inline int	check_option(t_env *env, char *arg, unsigned int *j)
{
	unsigned int	i;

	i = *j + 1;

	if (arg[i] != 'd' && arg[i] != 'n')
		return (1);
	if (env->nb_players == 0 && arg[i] == 'd'
			&& ft_is_whitespace(arg[i + 4])
			&& ft_strncmp(DUMP, &arg[i], 4) == 0
			&& get_dump(env, arg, &i))
		return (1);
	if (arg[i] == 'n' && ft_is_whitespace(arg[i + 1])
			&& get_id(env, arg, &i))
		return (1);
	*j = i;
	return (0);
}

static inline int	check_champion(t_env *env, char *arg, unsigned int *j)
{
	unsigned int	i;
	unsigned int	len;

	i = *j;
	len = get_name_len(&arg[i]); // limiter la taille du nom si besoin
	if (arg[i + len - 1] != 'r' || ft_strncmp(&arg[i + len - 4], EXT, 4)
			|| loader(env, &player[env->nb_players], &arg[i], (int)len))
		return (1);
	*j = i + len;
	return (0);
}

int					get_opt_champ(t_env *env, char *arg)
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	while (arg[i])
	{
		while (arg[i] && ft_is_whitespace(arg[i]))
			i++;
		if (arg[i] == '-' && (len = get_name_len(&arg[i])) > 4
			&& ft_strncmp(&arg[i + len - 4], EXT, 4))
		{
			if (check_option(env, arg, &i))
				return (1);
		}
		else if(ft_isascii(arg[i]))
			if (check_champion(env, arg, &i))
				return (1);
	}
	return (0);
}
