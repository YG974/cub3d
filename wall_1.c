/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:07 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_wall(t_struct *s)
{
	s->x = 0;
	while (s->x < s->win.x)
	{
		ft_ray_init(s);
		ft_ray_direction(s);
		ft_ray_hit(s);
		ft_wall_size(s);
		ft_wall_texture(s);
		ft_draw_walls(s);
		s->x++;
	}
	ft_sprite(s);
	/*free(s->img.ptr);*/
	/*free(s->img.adr);*/
}

void	ft_ray_init(t_struct *s)
{
	s->cam = 2 * s->x / (double)(s->win.x) - 1;
	s->ray.dir.x = s->p.dir.x + s->p.plane.x * s->cam;
	s->ray.dir.y = s->p.dir.y + s->p.plane.y * s->cam;
	s->ray.dd.x = sqrt(1 + pow(s->ray.dir.y, 2) / pow(s->ray.dir.x, 2));
	s->ray.dd.y = sqrt(1 + pow(s->ray.dir.x, 2) / pow(s->ray.dir.y, 2));
	s->ray.pos.x = (int)s->p.pos.x;
	s->ray.pos.y = (int)s->p.pos.y;
	s->wall.hit = 0;
}

void	ft_ray_direction(t_struct *s)
{
	if (s->ray.dir.x < 0)
	{
		s->wall.step.x = -1;
		s->ray.sd.x = (s->p.pos.x - s->ray.pos.x) * s->ray.dd.x;
	}
	else
	{
		s->wall.step.x = 1;
		s->ray.sd.x = (s->ray.pos.x + 1.0 - s->p.pos.x) * s->ray.dd.x;
	}
	if (s->ray.dir.y < 0)
	{
		s->wall.step.y = -1;
		s->ray.sd.y = (s->p.pos.y - s->ray.pos.y) * s->ray.dd.y;
	}
	else
	{
		s->wall.step.y = 1;
		s->ray.sd.y = (s->ray.pos.y + 1.0 - s->p.pos.y) * s->ray.dd.y;
	}
}

void	ft_ray_hit(t_struct *s)
{
	while (s->wall.hit == 0)
	{
		if (s->ray.sd.x < s->ray.sd.y)
		{
			s->ray.sd.x += s->ray.dd.x;
			s->ray.pos.x += s->wall.step.x;
			s->wall.side = 0;
		}
		else
		{
			s->ray.sd.y += s->ray.dd.y;
			s->ray.pos.y += s->wall.step.y;
			s->wall.side = 1;
		}
		if (s->map.tab[s->ray.pos.y][s->ray.pos.x] == '1')
			s->wall.hit = 1;
	}
}

void	ft_wall_size(t_struct *s)
{
	if (s->wall.side == 0)
		s->wall.perp_dist = fabs((s->ray.pos.x - s->p.pos.x +
					(1 - s->wall.step.x) / 2) / s->ray.dir.x);
	else
		s->wall.perp_dist = fabs((s->ray.pos.y - s->p.pos.y +
					(1 - s->wall.step.y) / 2) / s->ray.dir.y);
	s->wall.buf[s->x] = s->wall.perp_dist;
	s->wall.height = (int)(s->win.y / s->wall.perp_dist);
	s->wall.start = -s->wall.height / 2 + s->win.y / 2;
	s->wall.start = (s->wall.start > 0 ? s->wall.start : 0);
	s->wall.end = s->wall.height / 2 + s->win.y / 2;
	s->wall.end = (s->wall.end >= s->win.y ? s->win.y - 1 : s->wall.end);
	if (s->wall.side == 0)
		s->wall.x = s->p.pos.y + s->wall.perp_dist * s->ray.dir.y;
	else
		s->wall.x = s->p.pos.x + s->wall.perp_dist * s->ray.dir.x;
	s->wall.x -= floor(s->wall.x);
}
