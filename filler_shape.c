/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 16:24:26 by ozalisky          #+#    #+#             */
/*   Updated: 2018/06/04 17:11:45 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_free_piece(t_s *db)
{
	int i;

	i = 0;
	while (i < db->piece_y)
	{
		free(db->piece[i]);
		db->piece[i] = NULL;
		++i;
	}
	free(db->piece);
	db->piece = NULL;
}

int		ft_abs(int a)
{
	if (a < 0)
		return (a * -1);
	return (a);
}

void	ft_manhattan_distance(t_s *db, int y, int x)
{
	int i;
	int j;
	int temp;

	i = 0;
	while (i < db->map_y)
	{
		j = 0;
		while (j < db->map_x)
		{
			if (db->map[i][j] == db->enemy)
			{
				temp = ft_abs(y - i) + ft_abs(x - j);
				if (db->map[y][x] ^ '.')
				{
					if ((int)db->map[y][x] > temp)
						db->map[y][x] = (unsigned char)temp;
				}
				else if (db->map[y][x] == '.')
					db->map[y][x] = (unsigned char)temp;
			}
			++j;
		}
		++i;
	}
}

void	ft_calc_distance(t_s *db)
{
	int y;
	int x;

	x = 0;
	y = 0;
	while (y < db->map_y)
	{
		while (x < db->map_x)
		{
			if (db->map[y][x] == '.')
				ft_manhattan_distance(db, y, x);
			++x;
		}
		x = 0;
		++y;
	}
}

void	ft_get_shape(t_s *db)
{
	long i;

	i = 6;
	if (ft_isdigit(db->line[i]))
	{
		db->piece_y = ft_atoi(db->line + i);
		while (ft_isdigit(db->line[i]))
			++i;
		db->piece_x = ft_atoi(db->line + i);
	}
	free(db->line);
	i = 0;
	if (!(db->piece = (char**)malloc(sizeof(char*) * (db->piece_y))))
		ft_printf("%d %d\n", -1, -1);
	while (i < db->piece_y)
	{
		db->line = NULL;
		get_next_line(0, &db->line);
		db->piece[i] = db->line;
		++i;
	}
}
