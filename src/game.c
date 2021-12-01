/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:57:40 by mleblanc          #+#    #+#             */
/*   Updated: 2021/12/01 11:05:16 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "draw.h"
#include "config.h"
#include <mlx.h>
#include <math.h>
#include <stdlib.h>

void	init_game(t_game *game, void *mlx, void *win)
{
	int32_t		i;
	t_player	*p;

	p = &game->player;
	game->mlx = mlx;
	game->win = win;
	p->fov_ratio = FOV / 90.0;
	p->angle = deg_to_rad(0.0);
	p->dir.x = cos(p->angle);
	p->dir.y = sin(p->angle);
	p->pos = (t_vec2){2.5, 4.5};
	p->c_plane = vec2_unit(p->angle + deg_to_rad(90.0));
	p->c_plane = vec2_mul(p->c_plane, p->fov_ratio);
	game->buf3d = new_buffer(mlx, WIDTH, HEIGHT);
	game->wall = new_texture(mlx, "textures/pld.xpm");
	ft_gettime(&game->last_frame);
	game->dt = 0.0;
	i = 0;
	while (i < N_KEYS)
		game->keystate[i++] = false;
}

static void	update_screen(t_game *game)
{
	t_buffer	*buf3d;

	buf3d = game->buf3d;
	mlx_put_image_to_window(game->mlx, game->win, buf3d->img, 0, 0);
}

int	update(t_game *g)
{
	t_time	t;
	int32_t	w;
	int32_t	h;

	ft_gettime(&t);
	g->dt = (float)ft_timediff(g->last_frame, t);
	g->last_frame = t;
	update_player(&g->player, g->keystate, g->dt, g->world);
	w = g->buf3d->w;
	h = g->buf3d->h;
	draw_rect(g->buf3d, (t_vec2){0, 0}, (t_vec2){w, h / 2}, g->world->ceiling);
	draw_rect(g->buf3d, (t_vec2){0, h / 2}, (t_vec2){w, h}, g->world->floor);
	draw_view(g->buf3d, &g->player, g->world->tex, g->world->map);
	update_screen(g);
	return (0);
}

int	quit_game(t_game *game)
{
	destroy_buffer(game->mlx, game->buf3d);
	mlx_destroy_window(game->mlx, game->win);
	ft_strarr_free(game->world->map);
	exit(0);
}
