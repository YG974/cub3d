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
	/*printf("%d\n", s->p.key.a);*/
	return (1);
}

int		ft_key_release(int key, void *s)
{
	ft_switch_key_bol(s, key, 0);
	/*printf("%d\n", s->p.key.a);*/
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
	/*ft_key_move(key, s);*/
	return (1);
}

int		ft_key_move(int key, t_struct *s)
{
	if (key == ESC)
		exit(0);
	if (s->p.key.w)
		ft_move_forward(s, 1.0);
	if (s->p.key.a)
		ft_move_side(s, -1.0);
	if (s->p.key.s)
		ft_move_forward(s, -1.0);
	if (s->p.key.d)
		ft_move_side(s, 1.0);
	if (s->p.key.left)
		ft_rotate(s, -1.0);
	if (s->p.key.right)
		ft_rotate(s, 1.0);
	ft_wall(s);
	/*mlx_hook(s->win.ptr, 2, 1L<<0, ft_key_press, &s);*/
	/*mlx_hook(s->win.ptr, 3, 1L<<1, ft_key_release, &s);*/
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
