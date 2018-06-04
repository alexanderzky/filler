/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 16:31:52 by ozalisky          #+#    #+#             */
/*   Updated: 2018/06/04 16:33:27 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		ft_distance_eval(t_s *db)
{
	if (db->temp_distance == -1 || db->x_once > 1)
		return (0);
	if (db->distance > 0)
		if (db->temp_distance > db->distance)
			return (0);
	return (1);
}

void	ft_out_bonds_x(t_s *db)
{
	while (db->place_piece_x < db->piece_x &&
		   db->piece[db->place_piece_y][db->place_piece_x] ^ '*')
		++db->place_piece_x;
	if (db->piece[db->place_piece_y][db->place_piece_x] == '*')
		db->temp_distance = -1;
}

void	ft_if_star(t_s *db)
{
	if (db->map[db->temp_y][db->temp_x] == db->player_c)
		++db->x_once;
	else if (db->temp_y < db->map_y && db->temp_x < db->map_x)
		db->temp_distance += (int)db->map[db->temp_y][db->temp_x];
	++db->place_piece_x;
}

void	ft_out_of_bonds_y(t_s *db)
{
	while (db->place_piece_y < db->piece_y)
	{
		while (db->place_piece_x < db->piece_x &&
			   db->piece[db->place_piece_y][db->place_piece_x] ^ '*')
			++db->place_piece_x;
		if (db->piece[db->place_piece_y][db->place_piece_x] == '*')
			db->temp_distance = -1;
		db->place_piece_x = 0;
		++db->place_piece_y;
	}
}

void	ft_check_columns(t_s *db)
{
	if (db->piece[db->place_piece_y][db->place_piece_x] != '*')
		++db->place_piece_x;
	else if (db->piece[db->place_piece_y][db->place_piece_x] == '*' &&
			 db->map[db->temp_y][db->temp_x] == db->enemy)
		db->temp_distance = -1;
	else if (db->piece[db->place_piece_y][db->place_piece_x] == '*')
		ft_if_star(db);
	if (++db->temp_x >= db->map_x)
		ft_out_bonds_x(db);
}
