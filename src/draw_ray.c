/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:54:45 by mleblanc          #+#    #+#             */
/*   Updated: 2021/11/11 19:24:53 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "fixed_map.h"
#include <math.h>

static t_vec2i	get_step(t_vec2 dir)
{
	t_vec2i	step;

	if (dir.x < 0.0)
		step.x = -1;
	else
		step.x = 1;
	if (dir.y < 0.0)
		step.y = -1;
	else
		step.y = 1;
	return (step);
}

static t_vec2	fst_ray_len(t_vec2 dir, t_vec2 pos, t_vec2 unit, t_vec2i map)
{
	t_vec2	ray_len;

	if (dir.x < 0.0)
		ray_len.x = (pos.x - (double)map.x) * unit.x;
	else
		ray_len.x = ((double)(map.x + 1.0) - pos.x) * unit.x;
	if (dir.y < 0.0)
		ray_len.y = (pos.y - (double)map.y) * unit.y;
	else
		ray_len.y = ((double)(map.y + 1.0) - pos.y) * unit.y;
	return (ray_len);
}

static void	intersect(t_buffer *buf, t_vec2 hit, t_vec2 pos, uint32_t c)
{
	draw_line(buf, vec2_mul(pos, SQ_SIZE), vec2_mul(hit, SQ_SIZE), c);
}

void	draw_ray(t_buffer *buf, t_vec2 pos, t_vec2 dir, uint32_t c)
{
	t_vec2	ray_len;
	t_vec2	unit_step;
	t_vec2i	map_sq;
	t_vec2i	step;
	double	dist;

	unit_step.x = sqrt(1.0 + pow(dir.y / dir.x, 2.0));
	unit_step.y = sqrt(1.0 + pow(dir.x / dir.y, 2.0));
	map_sq = (t_vec2i){(int32_t)pos.x, (int32_t)pos.y};
	step = get_step(dir);
	ray_len = fst_ray_len(dir, pos, unit_step, map_sq);
	dist = 0.0;
	while (dist < 100.0)
	{
		if (ray_len.x < ray_len.y)
		{
			map_sq.x += step.x;
			dist = ray_len.x;
			ray_len.x += unit_step.x;
		}
		else
		{
			map_sq.y += step.y;
			dist = ray_len.y;
			ray_len.y += unit_step.y;
		}
		if (g_map[map_sq.y][map_sq.x] == 1)
		{
			intersect(buf, vec2_add(vec2_mul(dir, dist), pos), pos, c);
			break ;
		}
	}
}

void	draw_field(t_buffer *buf, t_player *p, uint32_t c)
{
	double	angle_step;
	double	angle;
	t_vec2	dir;

	angle_step = deg_to_rad(5.0);
	angle = p->angle - deg_to_rad(40.0);
	while (angle < p->angle + deg_to_rad(40.0))
	{
		dir.x = cos(angle);
		dir.y = sin(angle);
		draw_ray(buf, p->pos, dir, c);
		angle += angle_step;
	}
}
