/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   critical_points.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozlov <ikozlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 14:55:47 by ikozlov           #+#    #+#             */
/*   Updated: 2018/03/25 18:13:53 by ikozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "math.h"
#include <limits.h>

void	set_distance(t_point point, int x, int y, char p)
{
	int		d;
	int		player;

	player = ft_tolower(p) == PLAYER2;
	d = DISTANCE(x, y, point.x, point.y);
	if (point.distances[player] > d)
		point.distances[player] = d;
}

void	set_distances(t_point *cp, int x, int y, char p)
{
	int		i;

	i = -1;
	while (++i < C_POINTS)
		set_distance(cp[i], x, y, p);
}

t_point	get_opponents_last_move(t_game *game)
{
	int			i;
	int			j;
	char		**map;
	t_point		end;
	t_point		start;

	i = -1;
	SETXY(end, -1, -1);
	SETXY(start, -1, -1);
	map = MTX_TOCHAR(game->map.m);
	while (++i < game->map.rows && game->old_map.m != NULL)
	{
		j = -1;
		while (++j < game->map.cols)
			if (map[i][j] != MTX_TOCHAR(game->old_map.m)[i][j]
				&& ft_tolower(map[i][j]) == game->opponent)
			{
				start.x == -1 ? SETXY(start, j, i) : (void)0;
				end.x < j || end.y < i ? SETXY(end, j, i) : (void)0;
			}
	}
	SETXY(start, (start.x + end.x) / 2, (start.y + end.y) / 2);
	return (start);
}

void	set_main_critical_point(t_game *game)
{
	int			player;
	int			opponent;
	int			distance;

	player = game->player == PLAYER2;
	opponent = game->opponent == PLAYER2;
	distance = -1;
	game->critical_point = get_opponents_last_move(game);
	if (game->critical_point.x < 0 || game->critical_point.y < 0)
		SETXY(game->critical_point, game->map.cols / 2, game->map.rows / 2);
	ft_log("Return critical point at pos %d, %d\n", game->critical_point.x,
		game->critical_point.y);
}
