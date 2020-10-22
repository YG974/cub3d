/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:07 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_sprite_transform(t_struct *s)
{
	double	inv;

	inv = 0.0;
	s->sprite[s->i].delta.x = s->sprite[s->i].pos.x - s->p.pos.x;
	s->sprite[s->i].delta.y = s->sprite[s->i].pos.y - s->p.pos.y;
	inv = 1.0 / (s->p.plane.x * s->p.dir.y - s->p.plane.y * s->p.dir.x);
	s->sprite[s->i].depth.x = inv * (s->p.dir.y * s->sprite[s->i].delta.x -
		s->p.dir.x * s->sprite[s->i].delta.y);
	s->sprite[s->i].depth.y = inv * (s->p.plane.x * s->sprite[s->i].delta.y -
		s->p.plane.y * s->sprite[s->i].delta.x);
	s->sprite[s->i].screen = (int)((s->win.x / 2) *
		(1 + s->sprite[s->i].depth.x / s->sprite[s->i].depth.y));
	return ;
}

void	ft_sprite_size(t_struct *s)
{
	s->sprite[s->i].height = abs((int)(s->win.y / s->sprite[s->i].depth.y));
	s->sprite[s->i].start.y = (s->win.y / 2) - (s->sprite[s->i].height / 2);
	if (s->sprite[s->i].start.y < 0)
		s->sprite[s->i].start.y = 0;
	s->sprite[s->i].end.y = (s->win.y / 2) + (s->sprite[s->i].height / 2);
	if (s->sprite[s->i].end.y >= s->win.y)
		s->sprite[s->i].end.y = s->win.y - 1;
	s->sprite[s->i].width = abs((int)(s->win.y / s->sprite[s->i].depth.y));
	s->sprite[s->i].start.x = s->sprite[s->i].screen
		- (s->sprite[s->i].width / 2);
	if (s->sprite[s->i].start.x < 0)
		s->sprite[s->i].start.x = 0;
	s->sprite[s->i].end.x = s->sprite[s->i].screen + s->sprite[s->i].width / 2;
	if (s->sprite[s->i].end.x >= s->win.x)
		s->sprite[s->i].end.x = s->win.x - 1;
	return ;
}

void	ft_draw_sprite(t_struct *s)
{
	int		x;
	int		y;
	int		d;

	x = s->sprite[s->i].start.x;
	while (x < s->sprite[s->i].end.x)
	{
		s->tex.x = (int)(256 * (x - (-s->sprite[s->i].width / 2 +
				s->sprite[s->i].screen)) * 64 / s->sprite[s->i].width) / 256;
		y = s->sprite[s->i].start.y;
		while (y < s->sprite[s->i].end.y)
		{
			d = y * 256 - s->win.y * 128 + s->sprite[s->i].height * 128;
			s->tex.y = (int)((d * 64) / s->sprite[s->i].height) / 256;
			if (x > 0 && x < s->win.x && s->sprite[s->i].depth.y > 0 &&
					s->sprite[s->i].depth.y < s->wall.buf[x])
			{
				s->color = s->tex.sprite[64 * s->tex.y + s->tex.x];
				if (s->color != BLACK)
					s->img.adr[x + s->win.x * y] = s->color;
			}
			y++;
		}
		x++;
	}
}
