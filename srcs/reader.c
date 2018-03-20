/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozlov <ikozlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 19:17:54 by ikozlov           #+#    #+#             */
/*   Updated: 2018/03/19 21:10:04 by ikozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "get_next_line.h"

static void		get_matrix_size(t_matrix *matrix, int fd)
{
	char	*line;
	int		i;

	if (!get_next_line(STDIN_FILENO, &line))
		exit(1);
	while (!ft_isdigit(*(line + i)))
		i++;
	matrix->rows = ft_atoi(line + i);
	while (ft_isdigit(*(line + i)))
		i++;
	matrix->cols = ft_atoi(line + i);
	free(line);
}

static void		fill_matrix(t_matrix *matrix, int fd)
{
	int		i;

	i = -1;
	while (++i < matrix->rows)
		if (!get_next_line(fd, matrix->m + i))
			exit(1);
}

static void		get_map(t_game *game)
{
	char	*line;
	int		i;

	i = -1;
	get_matrix_size(&game->map, STDIN_FILENO);
	get_next_line(STDIN_FILENO, &line);
	free(line);
	game->map.m = malloc(sizeof(char *) * game->rows);
	fill_matrix(&game->map, STDIN_FILENO);
}

static void		get_piece(t_game *game)
{
	get_matrix_size(&game->piece, STDIN_FILENO);
	game->piece.m = malloc(sizeof(char *) * game->piece.rows);
	fill_matrix(&game->piece, STDIN_FILENO);
}

void	get_data(t_game *game)
{
	get_map(game);
	get_piece(game);
}
