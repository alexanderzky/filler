/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:40:21 by ozalisky          #+#    #+#             */
/*   Updated: 2018/06/02 17:36:18 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <math.h>
# include <stdio.h>
# include "./libft/libft.h"

typedef struct	s_t
{
	int 		fd; /*delete*/

	char		*line;
	int			player;
	int			map_y;
	int			map_x;
	unsigned char		**map;
	int			piece_y;
	int			piece_x;
	char		**piece;
	int			distance;
	int			print_y;
	int			print_x;
//	char		**figure;

	int			x_once;
	int			x_once_y;
	int			x_once_x;
	int			temp_distance;

	unsigned char enemy;
	unsigned char player_c;

}				t_s;




#endif //FILLER_FILLER_H
