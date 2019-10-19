/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:48:16 by moguy             #+#    #+#             */
/*   Updated: 2019/10/19 14:24:10 by moguy            ###   ########.fr       */
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
	static bool		id[4] = {0, 0, 0, 0};
	unsigned int	i;

	i = after_space(arg, *j + 1);
	if (!ft_is_whitespace(arg[i + 1])
			|| (env->player[env->nb_players].id = ft_atoi(&arg[i])) < 1
			|| env->player[env->nb_players].id > 4)
		return (error(BAD_ID, NULL));
	*j = after_word(arg, i) + 1;
	if (id[env->player[env->nb_players].id - 1] == 0)
		id[env->player[env->nb_players].id - 1] = 1;
	else 
		return (1);
	i = 0;
	while (i < (int)env->nb_players)
	{
		if (env->player[i].id == env->player[env->nb_players].id)
		{
			env->player[i].id = 0;
			env->player[i].id = find_id(env, env->nb_players + 1);
		}
		i++;
	}
	return (0);
}

static inline int	get_dump(t_env *env, char *arg, unsigned int *j)
{
	unsigned int	i;

	i = *j + 6;
	i = after_space(arg, i);
	if ((env->dump = ft_atoi(&arg[i])) < 1
			|| env->dump > INT_MAX)
		return (error(BAD_NUMBER, NULL));
	i = after_word(arg, i);
	*j = i;
	return (0);
}

static inline int	check_option(t_env *env, char *arg, unsigned int *j)
{
	unsigned int	i;

	i = *j + 1;

	if (arg[i] != 'n' || !ft_is_whitespace(arg[i + 1]))
		return (1);
	if (get_id(env, arg, &i))
		return (1);
	*j = i;
	return (0);
}

static inline int	check_champion(t_env *env, char *arg, unsigned int *j)
{
	unsigned int	i;
	unsigned int	len;

	i = *j;
	len = get_name_len(&arg[i]);
	if (ft_strncmp(&arg[i + len - 4], EXT, 4) != 0
			|| loader(env, &env->player[env->nb_players], &arg[i], (int)len))
		return (1);
	*j = i + len;
	return (0);
}

int					get_opt_champ(t_env *env, char *arg)
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	i = after_space(arg, i);
	if (ft_strncmp(&arg[i], DUMP, 6) == 0)
		if (get_dump(env, arg, &i))
			return (1);
	while (arg[i])
	{
		i = after_space(arg, i);
		if (arg[i] == '-' && (len = get_name_len(&arg[i]))
				&& ft_strncmp(&arg[i + len - 4], EXT, 4) != 0)
		{
			if (check_option(env, arg, &i))
				return (1);
		}
		else
			if (check_champion(env, arg, &i))
				return (1);
	}
	return (0);
}
