/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
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
	return (0);
}

int		ft_key_release(int key, void *s)
{
	ft_switch_key_bol(s, key, 0);
	return (0);
}

int		ft_switch_key_bol(t_struct *s, int key, int value)
{
	if (key == ESC)
		s->p.key.esc = value;
	if (key == KEY_W)
		s->p.key.w = value;
	if (key == KEY_A)
		s->p.key.a = value;
	if (key == KEY_S)
		s->p.key.s = value;
	if (key == KEY_D)
		s->p.key.d = value;
	if (key == KEY_LEFT)
		s->p.key.left = value;
	if (key == KEY_RIGHT)
		s->p.key.right = value;
	return (1);
}

int		ft_key_move(t_struct *s)
{
	if (s->p.key.esc)
		exit(0);
	if (s->p.key.w)
		ft_move_forward(s, 1);
	if (s->p.key.a)
		ft_move_side(s, -1);
	if (s->p.key.s)
		ft_move_forward(s, -1);
	if (s->p.key.d)
		ft_move_side(s, 1);
	if (s->p.key.left)
		ft_rotate(s, -1);
	if (s->p.key.right)
		ft_rotate(s, 1);
	ft_wall(s);
	return (1);
}
