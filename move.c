/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:07 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_move_forward(t_struct *s, double sign)
{
	int		x;
	int		y;
	double	speed;
	
	speed = 0.11;
	mlx_destroy_image(s->mlx, s->img.ptr);
	x = (int)(s->p.pos.x + sign * s->p.dir.x * speed);
	y = (int)(s->p.pos.y + sign * s->p.dir.y * speed);
	if (s->map.tab[(int)(s->p.pos.y)][(int)(x)] == '0')
		s->p.pos.x += sign * s->p.dir.x * speed;
	if (s->map.tab[(int)(y)][(int)s->p.pos.x] == '0')
		s->p.pos.y += sign * s->p.dir.y * speed;
	ft_expose(s);
	return ;
}

void	ft_move_side(t_struct *s, double sign)
{
	double	speed;
	
	speed = 0.11;
	mlx_destroy_image(s->mlx, s->img.ptr);
	if (s->map.tab[(int)(s->p.pos.y)]
			[(int)(s->p.pos.x + sign * -s->p.dir.y * speed)] == '0')
		s->p.pos.x += sign * -s->p.dir.y * speed;
	if (s->map.tab[(int)(s->p.pos.y + sign * s->p.dir.x * speed)]
			[(int)s->p.pos.x] == '0')
		s->p.pos.y += sign * s->p.dir.x * speed;
	ft_expose(s);
	return ;
}

void	ft_rotate(t_struct *s, double sign)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	rot = 0.01 * sign;
	old_dir_x = s->p.dir.x;
	old_plane_x = s->p.plane.x;
	s->p.dir.x = s->p.dir.x * cos(rot) - s->p.dir.y * sin(rot);
	s->p.dir.y = old_dir_x * sin(rot) + s->p.dir.y * cos(rot);
	s->p.plane.x = s->p.plane.x * cos(rot) - s->p.plane.y * sin(rot);
	s->p.plane.y = old_plane_x * sin(rot) + s->p.plane.y * cos(rot);
	ft_expose(s);
	return ;
}
