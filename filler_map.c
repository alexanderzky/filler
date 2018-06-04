/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 16:19:42 by ozalisky          #+#    #+#             */
/*   Updated: 2018/06/04 16:24:20 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_get_player(t_s *db)
{
	if (ft_strcmp(db->line, "$$$ exec p1 : [./ozalisky.filler]") == 0)
	{
		db->player = 1;
		db->enemy = (unsigned char)220;
		db->player_c = (unsigned char)230;
	}
	else if (ft_strcmp(db->line, "$$$ exec p2 : [./ozalisky.filler]") == 0)
	{
		db->player = 2;
		db->enemy = (unsigned char)230;
		db->player_c = (unsigned char)220;
	}
	free(db->line);
}

void	ft_replace_players(t_s *db)
{
	int k = 0;
	int j = 0;
	while (k < db->map_y)
	{
		while (j < db->map_x)
		{
			if (db->map[k][j] == 'X' || db->map[k][j] == 'x')
				db->map[k][j] = (unsigned char)220;
			else if (db->map[k][j] == 'O' || db->map[k][j] == 'o')
				db->map[k][j] = (unsigned char)230;
			++j;
		}
		j = 0;
		++k;
	}
}

void	ft_get_map_piece_size(t_s *db, long i)
{
	db->map_y = ft_atoi(db->line + i);
	while (ft_isdigit(db->line[i]))
		++i;
	db->map_x = ft_atoi(db->line + i);
}

void	ft_get_map(t_s *db)
{
	long i;

	i = 0;
	ft_get_map_piece_size(db, 8);
	free(db->line);
	get_next_line(db->fd, &db->line);
	free(db->line);
	if (!(db->map = (unsigned char**)ft_memalloc(sizeof(unsigned char*) *
												 (db->map_y))))
		ft_printf("%d %d\n", -1, -1);
	while(i < db->map_y)
	{
		db->line = NULL;
		get_next_line(db->fd, &db->line);
		db->map[i] = (unsigned char*)db->line + 4;
		++i;
	}
	ft_replace_players(db);
}

void	ft_free_map(t_s *db)
{
	int i;

	i = 0;
	while (i < db->map_y)
	{
		free(db->map[i] - 4);
		db->map[i] = NULL;
		++i;
	}
	free(db->map);
	db->map = NULL;
}
