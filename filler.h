/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:40:21 by ozalisky          #+#    #+#             */
/*   Updated: 2018/05/31 11:51:00 by ozalisky         ###   ########.fr       */
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
	char		**map;
	int			piece_y;
	int			piece_x;
	char		**piece;
	int			distance;
	int			print_y;
	int			print_x;
//	char		**figure;

	int			x_once;
	int			temp_distance;

}				t_s;




#endif //FILLER_FILLER_H
