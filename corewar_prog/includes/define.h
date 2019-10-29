/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:14:20 by moguy             #+#    #+#             */
/*   Updated: 2019/10/26 23:02:16 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

//ERROR

# define BAD_ARGS "Bad arguments"
# define BAD_ID "ID is not between 1 and current number of player."
# define BAD_DUMP "Dump isn't between 1 and INT_MAX."
# define BAD_FILE "Can't Open or Read one of the file."
# define LST_ERR "List error."
# define MALLOC_ERR "Malloc error."
# define TOO_MANY_ARGS "Too many arguments, only 4 champions can fight in the area at once..."
# define TOO_MANY_PLAYERS "Too many players, only 4 champions can fight in the area at once..."
# define USAGE "Usage: /vm [-dump nbr_cycles] [[-n number between 1 and number of players] champion1.cor] ..."
# define VM_ERR "Virtual machine error."

//PARSING

//LIMITE

# define MAX_ARGS 32
# define MAX_CYCLE 1000000
# define PAD_LENGTH 4
# define NB_FUNC 16
# define OPT_MAX 2
# define VERB_MAX 2

//NAME

# define DUMP "-dump "
# define OPT_N "-n "
# define EXT ".cor"

//BINARY_MASK

# define MASK_ENCO 0x03

#endif
