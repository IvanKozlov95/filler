/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:59:15 by ikozlov           #+#    #+#             */
/*   Updated: 2018/09/09 18:02:25 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

# define PLAYER1 'o'
# define PLAYER2 'x'
# define C_POINTS 5
# define FITNESS_MAX 1000

# define DEBUG 0
# define READ_FROM_FAKE 0

# define MTX_TOINT(m) (((int **)m))
# define MTX_TOCHAR(m) (((char **)m))

struct					s_matrix
{
	void				**m;
	int					rows;
	int					cols;
};
typedef struct s_matrix	t_matrix;

struct					s_game
{
	char				player;
	char				opponent;
	t_point				critical_point;
	t_list				*enemy;
	t_matrix			piece;
	t_matrix			map;
	t_matrix			old_map;
	t_matrix			fitness;
};
typedef struct s_game	t_game;

void					get_data(t_game *game, int fd);
void					whoami(t_game *game, int fd);
int						gameon(t_game *game, int fd);
void					die(char *msg);

void					ft_log(char *msg, ...);
void					log_matrix(t_matrix m);
void					log_critical_points(t_point *p);
void					log_fitness_matrix(int **m, int rows, int cols);

void					set_main_critical_point(t_game *game);

void					build_fitness_matrix(t_game *game);

void					free_matrix(t_matrix *m);

#endif
