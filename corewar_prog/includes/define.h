/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:14:20 by moguy             #+#    #+#             */
/*   Updated: 2019/10/31 19:34:34 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

//ERROR

# define BAD_ARGS "Bad arguments."
# define BAD_ID "ID is not between 1 and number of players."
# define BAD_DUMP "Dump value isn't between 1 and INT_MAX."
# define BAD_FILE "File invalid."
# define BAD_FILE_OPEN "Opening of one of the file failed."
# define BAD_FILE_READ "Reading of one of the file failed."
# define BAD_MAGIC "Magic number defined in the header of one of the \
	file is invalid. Magic has to be COREWAR_EXEC_MAGIC."
# define BAD_OPT "This option don't exist."
# define BAD_SIZE "The size define in the header of one of the file is \
	invalid. Size can't be more than CHAMP_MAX_SIZE."
# define CODE "Size of the redcode is too long, or diffent than the size \
	defined in the header."
# define LST_ERR "A process failed to be created, malloc error."
# define MALLOC_ERR "Malloc error."
# define SAME_ID "Some players has the same attributed ID."
# define TOO_MANY_ARGS "Too many arguments to the ./corewar call."
# define TOO_MANY_PLAYERS "Too many players, only 4 champions can fight in \
	the area at once, for at least one champion..."
# define VM_ERR "Virtual machine error."
# define USAGE "Usage: /vm [-dump nbr_cycles] [[-n number between \
	1 and number of players] champion1.cor] ..."

//PARSING

//LIMITE

# define MAX_ARGS 32
# define MAX_CYCLE 1000000
# define PAD_LENGTH 4
# define NB_FUNC 16
# define OPT_MAX 2
# define VERB_MAX 5
# define DUMP_LENGTH 12295

//NAME

# define DUMP "-dump "
# define OPT_N "-n "
# define EXT ".cor"

//BINARY_MASK

# define MASK_ENCO 0x03

#endif
