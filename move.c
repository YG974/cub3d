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

int		ft_key_press(int key, void *s)
{
	ft_switch_key_bol(s, key, 1);
	return (1);
}

int		ft_key_release(int key, void *s)
{
	ft_switch_key_bol(s, key, 0);
	return (1);
}

int		ft_switch_key_bol(t_struct *s, int key, int value)
{
	if (key == KEY_W)
		s->p.key.w = value;
	else if (key == KEY_A)
		s->p.key.a = value;
	else if (key == KEY_S)
		s->p.key.s = value;
	else if (key == KEY_D)
		s->p.key.d = value;
	else if (key == KEY_LEFT)
		s->p.key.left = value;
	else if (key == KEY_RIGHT)
		s->p.key.right = value;
	return (1);
}

int		ft_key_move(int key, t_struct *s)
{
	if (key == ESC)
		exit(0);
	if (s->p.key.w == 1)
		ft_move_forward(s, 1);
	if (s->p.key.a == 1)
		ft_move_side(s, -1);
	if (s->p.key.s == 1)
		ft_move_forward(s, -1);
	if (s->p.key.d == 1)
		ft_move_side(s, 1);
	if (s->p.key.left == 1)
		ft_rotate(s, -1);
	if (s->p.key.right == 1)
		ft_rotate(s, 1);
	ft_wall(s);
	mlx_put_image_to_window(s->mlx, s->win.ptr, s->img.ptr, 0, 0);
	return (1);
}

void	ft_move_forward(t_struct *s, double sign)
{
	int		x;
	int		y;

	x = (int)(s->p.pos.x + sign * s->p.dir.x * SPEED);
	y = (int)(s->p.pos.y + sign * s->p.dir.y * SPEED);
	if (s->map.tab[(int)(s->p.pos.y)][(int)(x)] == '0')
		s->p.pos.x += sign * s->p.dir.x * SPEED;
	if (s->map.tab[(int)(y)][(int)s->p.pos.x] == '0')
		s->p.pos.y += sign * s->p.dir.y * SPEED;
}

void	ft_move_side(t_struct *s, double sign)
{
	if (s->map.tab[(int)(s->p.pos.y)]
			[(int)(s->p.pos.x + sign * -s->p.dir.y * SPEED)] == '0')
		s->p.pos.x += sign * -s->p.dir.y * SPEED;
	if (s->map.tab[(int)(s->p.pos.y + sign * s->p.dir.x * SPEED)]
			[(int)s->p.pos.x] == '0')
		s->p.pos.y += sign * s->p.dir.x * SPEED;
}

void	ft_rotate(t_struct *s, double sign)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	rot = ANGLE * sign;
	old_dir_x = s->p.dir.x;
	old_plane_x = s->p.plane.x;
	s->p.dir.x = s->p.dir.x * cos(rot) - s->p.dir.y * sin(rot);
	s->p.dir.y = old_dir_x * sin(rot) + s->p.dir.y * cos(rot);
	s->p.plane.x = s->p.plane.x * cos(rot) - s->p.plane.y * sin(rot);
	s->p.plane.y = old_plane_x * sin(rot) + s->p.plane.y * cos(rot);
}
