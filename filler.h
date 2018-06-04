/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:40:21 by ozalisky          #+#    #+#             */
/*   Updated: 2018/06/04 16:33:27 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "./libft/libft.h"

typedef struct		s_t
{
	int 			fd; /*delete*/
	char			*line;
	int				player;
	int				map_y;
	int				map_x;
	unsigned char	**map;
	int				piece_y;
	int				piece_x;
	char			**piece;
	int				distance;
	int				print_y;
	int				print_x;
	int				x_once;
	int				temp_distance;
	unsigned char	enemy;
	unsigned char	player_c;
	int				temp_y;
	int				temp_x;
	int				place_piece_y;
	int				place_piece_x;
}					t_s;
void				ft_get_map(t_s *db);
void				ft_get_map_piece_size(t_s *db, long i);
void				ft_free_map(t_s *db);
void				ft_get_shape(t_s *db);
void				ft_calc_distance(t_s *db);
void				ft_free_piece(t_s *db);
int					ft_distance_eval(t_s *db);
void				ft_out_bonds_x(t_s *db);
void				ft_if_star(t_s *db);
void				ft_out_of_bonds_y(t_s *db);
void				ft_check_columns(t_s *db);
void				ft_get_player(t_s *db);
#endif //FILLER_FILLER_H
