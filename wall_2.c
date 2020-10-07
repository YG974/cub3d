/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:07 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_wall_texture(t_struct *s)
{
	s->tex.x = (int)(s->wall.x * s->tex.width);
	if (s->wall.side == 0 && s->ray.dir.x > 0)
		s->tex.x = s->tex.width - s->tex.x - 1;
	if (s->wall.side == 1 && s->ray.dir.y < 0)
		s->tex.x = s->tex.width - s->tex.x - 1;
	s->tex.step = (double)s->tex.width / s->wall.height;
	s->tex.pos = (s->wall.start - s->win.y / 2 + s->wall.height / 2)
		* s->tex.step;
}

void	ft_draw_walls(t_struct *s)
{
	s->color = s->sky.r * 256 * 256 + s->sky.g * 256 + s->sky.b;
	s->y = 0;
	while (s->y < s->wall.start)
		s->img.adr[s->x + s->win.x * s->y++] = s->color;
	while (s->y >= s->wall.start && s->y <= s->wall.end)
	{
		s->tex.y = (int)s->tex.pos;
		s->tex.pos += s->tex.step;
		ft_pixel(s);
		s->y++;
	}
	s->color = s->floor.r * 256 * 256 + s->floor.g * 256 + s->floor.b;
	while (s->y < s->win.y)
		s->img.adr[s->x + s->win.x * s->y++] = s->color;
}

void	ft_pixel(t_struct *s)
{
	int	pix_nb;

	pix_nb = s->tex.width * s->tex.y + s->tex.x;
	if (s->wall.side == 0)
	{
		if (s->wall.step.x < 0)
			s->img.adr[s->x + s->win.x * s->y] = s->tex.w[pix_nb];
		else
			s->img.adr[s->x + s->win.x * s->y] = s->tex.e[pix_nb];
	}
	else
	{
		if (s->wall.step.y < 0)
			s->img.adr[s->x + s->win.x * s->y] = s->tex.n[pix_nb];
		else
			s->img.adr[s->x + s->win.x * s->y] = s->tex.s[pix_nb];
	}
}
