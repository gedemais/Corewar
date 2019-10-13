/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:14:20 by moguy             #+#    #+#             */
/*   Updated: 2019/10/13 16:57:30 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

//ERROR

# define USAGE "Usage: /vm [-dump nbr_cycles] [[-n number] champion1.cor] ..."
# define TOO_MANY_ARGS "Too many arguments, only 4 champions can fight in the area at once..."
# define BAD_ARGS "Bad option or file."
# define FILE_ERR_MSG "Can't Open or Read one of the file."
# define BAD_NUMBER "Dump or number are not integers."

//PARSING

# define MAX_ARGS 32
# define DUMP "dump"
# define EXT ".cor"

#endif
