/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozlov <ikozlov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 18:47:36 by ikozlov           #+#    #+#             */
/*   Updated: 2018/03/19 19:13:00 by ikozlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "get_hext_line.h"

int		gameon(t_game *game)
{

}

void	whoami(t_game *game)
{
	char	*line;
	
	if (!get_next_line(STDERR_FILENO, &line))
		exit(0);
	line = ft_strchr(line, 'p');
	if (*(line + 1) == '1')
		game->player = 'o';
	else
		game->player = 'x';
	free(line);
}

int		main(void)
{
	t_game	game;
	
	whoami(&game);
	while (gameon(&game))
		continue ;
	return (0);
}