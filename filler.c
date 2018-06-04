/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:40:01 by ozalisky          #+#    #+#             */
/*   Updated: 2018/06/04 16:33:27 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_save_distance(t_s *db, int y, int x)
{
	if (db->distance == 0)
	{
		db->distance = db->temp_distance;
		db->print_y = y;
		db->print_x = x;
	}
	else if (db->temp_distance < db->distance ||
			(db->temp_distance <= db->distance && db->player == 2 &&
					y < db->print_y && db->map_y < 20))
	{
		db->distance = db->temp_distance;
		db->print_y = y;
		db->print_x = x;
	}
}

void	ft_check_placement(t_s *db, int y, int x)
{
	db->temp_y = y;
	db->temp_x = x;
	db->temp_distance = 0;
	db->x_once = 0;
	db->place_piece_y = 0;
	db->place_piece_x = 0;
	while (db->place_piece_y < db->piece_y && ft_distance_eval(db))
	{
		db->place_piece_x = 0;
		while (db->place_piece_x < db->piece_x && ft_distance_eval(db))
			ft_check_columns(db);
		db->place_piece_x = 0;
		++db->place_piece_y;
		if (++db->temp_y >= db->map_y)
			ft_out_of_bonds_y(db);
		db->temp_x = x;
	}
	if (db->x_once == 1 && ft_distance_eval(db))
		ft_save_distance(db, y, x);
}

void	ft_make_move(t_s *db)
{
	int y;
	int x;
	int delta_y;
	int delta_x;

	y = 0;
	while (y < db->map_y)
	{
		x = 0;
		while (x < db->map_x)
		{
			delta_y = 0;
			delta_x = 0;
			while (db->map[y][x] == db->player_c && delta_y < db->piece_y &&
					y - delta_y > -1)
			{
				while (delta_x < db->piece_x && x - delta_x > -1)
					ft_check_placement(db, y - delta_y, x - delta_x++);
				++delta_y;
				delta_x = 0;
			}
			++x;
		}
		++y;
	}
}

void	ft_read_game(t_s *db)
{
	if (db->line[0] == '$' && db->player == 0)
		ft_get_player(db);
	else if (db->line[0] == 'P' && db->line[1] == 'l')
		ft_get_map(db);
	else if (db->line[0] == 'P' && db->line[1] == 'i')
	{
		ft_get_shape(db);
		ft_calc_distance(db);
		ft_make_move(db);
		if (db->print_y > -1 && db->print_x > -1)
			ft_printf("%d %d\n", db->print_y, db->print_x);
		ft_free_map(db);
		ft_free_piece(db);
		db->distance = 0;
	}
	else
		free(db->line);
}

int		main(void)
{
	t_s		*db;
	if ((db = (t_s *)ft_memalloc(sizeof(t_s))))
	{
//		db->fd = open("file2", O_RDONLY);
		db->fd = 0;
		while (get_next_line(db->fd, &db->line) > 0)
		{
			ft_read_game(db);
			db->print_y = 0;
			db->print_x = 0;
		}
	}
	else
		ft_printf("%d %d\n", -1, -1);
	free(db);
	exit(0);
}
