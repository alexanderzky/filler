/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:40:01 by ozalisky          #+#    #+#             */
/*   Updated: 2018/05/31 12:07:04 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "filler.h"

void	ft_get_player(t_s *db)
{
	if (ft_strcmp(db->line, "$$$ exec p1 : [./ozalisky.filler]") == 0)
		db->player = 1;
	else if (ft_strcmp(db->line, "$$$ exec p2 : [./ozalisky.filler]") == 0)
		db->player = 2;
//	free(db->line);
}

void	write_coord(t_s *db)
{
	ft_putnbr(db->print_y);
	write(1, " ", 1);
	ft_putnbr(db->print_x);
	write(1, "\n", 1);
//	ft_printf("_____");
}

void	ft_check_placement(t_s *db, int y, int x) /*if player == 2*/
{
	int i;
	int j;
	int temp_y = y;
	int temp_x = x;


	db->temp_distance = 0;
	db->x_once = 0;
	i = db->piece_y - 1;
	j = db->piece_x - 1;
	while (i > -1)
	{
		while (j > -1)
		{
			while (db->piece[i][j] != '*' && j >= 0)
			{
				j--;
			}
			if (db->piece[i][j] == '*')
			{
				if (ft_tolower(db->map[temp_y][temp_x]) == 'x')
				{
					db->x_once++;
				}
				else if (temp_y < db->map_y && temp_x < db->map_x)
				{
					db->temp_distance += (int)db->map[temp_y][temp_x];
				}
				if (db->x_once > 1)
				{
					db->temp_distance = -1;
					break ;
				}
			}
			if (db->temp_distance == -1)
				break ;
			if (temp_x - 1 > -1 && j - 1 > -1)
			{
				temp_x--;
			}
			j--;
		}
		if (db->temp_distance == -1)
			break ;
		j = db->piece_x - 1;
		if (temp_y - 1 > -1 && i - 1 > -1)
		{
			temp_y--;
			temp_x = x;
		}
		i--;
	}
	if (db->x_once == 1)
	{
		db->print_y = temp_y;
		db->print_x = temp_x;
		if (db->distance == 0)
		{
			db->distance = db->temp_distance;
		}
		else if (db->temp_distance < db->distance)
		{
			db->distance = db->temp_distance;
		}
	}
}

void	ft_make_move(t_s *db)
{
	int i;
	int j;

	int piece_y = 0;
	int piece_x = 0;

	int delta_y = 0;
	int delta_x = 0;

	i = 0;
	j = 0;
	while (i < db->map_y)
	{
		while (j < db->map_x)
		{
			if (ft_tolower(db->map[i][j]) == 'x')
			{
				while (piece_y < db->piece_y && i - delta_y > -1)
				{
					while (piece_x < db->piece_x && j - delta_x > -1)
					{
						ft_check_placement(db, i - delta_y, j - delta_x);
						delta_x++;
						piece_x++;
					}
					delta_y++;
					piece_y++;
					delta_x = 0;
					piece_x = 0;
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
}

int	ft_abs(int a)
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
	j = 0;
	while (i < db->map_y)
	{
		while (j < db->map_x)
		{
			if (db->map[i][j] == 'o' || db->map[i][j] == 'O')
			{
				temp = ft_abs(y - i) + ft_abs(x - j);
				if (db->map[y][x] != '.')
				{
					if ((int)db->map[y][x] > temp)
					{
						db->map[y][x] = (unsigned char)temp;
					}
				}
				else
					db->map[y][x] = (unsigned char)temp;
			}
			j++;
		}
		j = 0;
		i++;
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
			if (ft_tolower(db->map[y][x]) != 'o' &&
				ft_tolower(db->map[y][x]) != 'x')
			{
				ft_manhattan_distance(db, y, x);
			}
			x++;
		}
		x = 0;
		y++;
	}
}

//void	ft_get_figure(t_s *db)
//{
//
//
//
////	char	*str;
////	long i = 0;
////	long j = 0;
////
////	free(db->line);
////	while (i < db->piece_y)
////	{
////		get_next_line(db->fd, &db->line);
////		str = db->line;
////		while (j < db->piece_x)
////		{
////			if (str != "." && str[j] == '*')
////				db->piece[i][j] = '*';
////			j++;
////		}
////		j = 0;
////		i++;
////	}
////	ft_make_move(db);
//}

void	ft_get_shape(t_s *db)
{
	long i;

	i = 0;
	while (!ft_isdigit(db->line[i]))
		i++;
	if (ft_isdigit(db->line[i]))
	{
		db->piece_y = ft_atoi(db->line + i);
		while (ft_isdigit(db->line[i]))
			i++;
		db->piece_x = ft_atoi(db->line + i);
	}

	i = 0;
	db->piece = (char**)malloc(sizeof(char)* (db->piece_y));
	while(i < db->piece_y)
	{
//		free(db->line);
		get_next_line(db->fd, &db->line);
//		db->piece[i] = (char*)malloc(sizeof(char)* (db->piece_x + 1));
		db->piece[i] = db->line;
//		ft_memset(db->piece[i], '.', db->piece_x);
//		db->piece[i][db->piece_x] = '\0';
		i++;
	}
//	ft_get_figure(db);
}



/*void	ft_get_posted_dots(t_s *db)
{
	char	*str;
	long i = 0;
	long j = 0;
	while (i < db->map_y)
	{
		get_next_line(db->fd, &db->line);
		str = db->line + 4;
		while (j < db->map_x)
		{
			if (str != "." && (str[j] == 'O' || str[j] == 'o'))
				db->map[i][j] = 'o';
			else if (str != "." && (str[j] == 'X' || str[j] == 'x'))
				db->map[i][j] = 'x';
			j++;
		}
		j = 0;
		i++;
	}
}*/

void	ft_get_map(t_s *db)
{
	long i;

	i = 8;
	while (!ft_isdigit(db->line[i]))
		i++;
	if (ft_isdigit(db->line[i]))
	{
		db->map_y = ft_atoi(db->line + i);
		while (ft_isdigit(db->line[i]))
			i++;
		db->map_x = ft_atoi(db->line + i);
	}
//	free(db->line);
	get_next_line(db->fd, &db->line);
//	free(db->line);
	i = 0;
	if (db->map == NULL)
	{
		db->map = (char**)ft_memalloc(sizeof(char*) * (db->map_y));
		while(i < db->map_y)
		{
			db->line = NULL;
			get_next_line(db->fd, &db->line);
			db->map[i] = db->line + 4; //для free делать -4
//			free(db->line);
//			db->map[i] = (char*)malloc(sizeof(char)* (db->map_x + 1));
//			ft_memset(db->map[i], '.', db->map_x);
//			db->map[i][db->map_x] = '\0';
			i++;
		}
	}
//	ft_get_posted_dots(db);
//	ft_make_move(db);
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
		if (db->print_y > 0 && db->print_x > 0)
			ft_printf("%d %d\n", db->print_y, db->print_x);
		int i = 0;
		while (i < db->map_y)
		{
			free(db->map[i] - 4);
			db->map[i] = NULL;
			i++;
		}
		free(db->map);
		db->map = NULL;
		i = 0;
		while (i < db->piece_y)
		{
			free(db->piece[i]);
			db->piece[i] = NULL;
			i++;
		}
		free(db->piece);
		db->piece = NULL;
		db->distance = 0;
	}

}

int		main(void)
{
	t_s		*db;
//	ft_strnequ("Plateau", line, 7)
	if ((db = (t_s *)ft_memalloc(sizeof(t_s))))
	{
//		db->fd = open("file2", O_RDONLY);
		db->fd = 0;
		while (get_next_line(db->fd, &db->line) > 0)
		{
			ft_read_game(db);


		}
	}
	free(db);
	return (0);
}
