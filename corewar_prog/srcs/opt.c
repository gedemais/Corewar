/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 22:18:40 by moguy             #+#    #+#             */
/*   Updated: 2019/10/26 22:27:35 by moguy            ###   ########.fr       */
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

int		get_dump(char *arg, unsigned int *j)
{
	unsigned int	i;
	long long int	dump;

	i = *j + 6;
	i = after_space(arg, i);
	if (!ft_isdigit(arg[i]) || (dump = ft_atoi(&arg[i])) < 1 || dump > INT_MAX)
		return (-1);
	while (ft_isdigit(arg[i]))
		i++;
	if (!ft_is_whitespace(arg[i]))
		return (-1);
	*j = i;
	return ((int)dump);
}
