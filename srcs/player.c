/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozlov <ikozlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 19:19:06 by ikozlov           #+#    #+#             */
/*   Updated: 2018/03/26 18:48:46 by ikozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <limits.h>

void	send_move(int row, int column)
{
	ft_log("Placing a piece at %d %d\n", row, column);
	ft_putnbr(row);
	write(STDOUT_FILENO, SPACE, 1);
	ft_putnbr(column);
	write(STDOUT_FILENO, NEW_LINE, 1);
}

int		get_sum(int **fitness, t_matrix p, int row, int col)
{
	int		i;
	int		j;
	int		hit_self;
	int		sum;

	i = -1;
	sum = 0;
	hit_self = 0;
	while (++i < p.rows)
	{
		j = -1;
		while (++j < p.cols)
			if (MTX_TOCHAR(p.m)[i][j] == '*')
			{
				if (fitness[row + i][col + j] == 0)
					hit_self++;
				else if (fitness[row + i][col + j] == -1)
					return (0);
				sum += fitness[row + i][col + j];
			}
	}
	if (hit_self != 1)
		sum = 0;
	return (sum);
}

int		*get_move(t_game *game)
{
	int		i;
	int		j;
	int		sum;
	int		tmp;
	int		*res;

	i = -1;
	res = (int *)ft_memalloc(2);
	sum = 0;
	while (++i < game->fitness.rows - game->piece.rows)
	{
		j = -1;
		while (++j < game->fitness.cols - game->piece.cols)
		{
			tmp = get_sum(MTX_TOINT(game->fitness.m), game->piece, i, j);
			if (tmp > sum)
			{
				res[0] = i - game->piece.rows;
				res[1] = j - game->piece.cols;
				sum = tmp;
			}
		}
	}
	return (res);
}

int		gameon(t_game *game, int fd)
{
	int		*move;

	get_data(game, fd);
	set_main_critical_point(game);
	build_fitness_matrix(game);
	ft_log("New trun\n");
	log_matrix(game->map);
	log_matrix(game->piece);
	// log_fitness_matrix(MTX_TOINT(game->fitness.m),
		// game->fitness.rows, game->fitness.cols);
	move = get_move(game);
	send_move(move[0], move[1]);
	if (game->old_map.m != NULL)
		free_matrix(&game->old_map);
	game->old_map = game->map;
	free_matrix(&game->piece);
	free_matrix(&game->fitness);
	free(move);
	return (1);
}
