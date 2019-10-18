/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:14:20 by moguy             #+#    #+#             */
/*   Updated: 2019/10/18 13:45:47 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

//ERROR

# define USAGE "Usage: /vm [-dump nbr_cycles] [[-n number] champion1.cor] ..."
# define TOO_MANY_ARGS "Too many arguments, only 4 champions can fight in the area at once..."
# define BAD_ARGS "Bad option or file."
# define FILE_ERR_MSG "Can't Open or Read one of the file."
# define BAD_NUMBER "Dump isn't between 1 and INT_MAX."
# define BAD_ID "ID is not between 1 and number_player."
# define VM_ERR "Virtual machine error."
# define MALLOC_ERR "Malloc error."
//PARSING

//LIMITE

# define MAX_ARGS 32
# define MAX_ARG_FUNC 3
# define MAX_CYCLE 1000000
# define NB_FUNC 16

//NAME

# define DUMP "-dump "
# define EXT ".cor"
# define BAD_FILE "File Error."

#endif
