/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:07 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
int		manage_key(int key, void *param)
{
	if (key == ESC)
		ft_escape(win_ptr);
	else if (key == A)
		ft_a(win
	return (1);
}

int main ()
{
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "42");
	mlx_pixel_put(mlx_ptr, win_ptr, 50, 50, 0xFFFFFF);
	mlx_key_hook(win_ptr, manage_key, (void *)0);
	mlx_loop(mlx_ptr);
	return (0);
}

int		ft_escape(t_struct s, void *win_ptr)
{
	write(1, "escape", 6);
	return (0);
}
