/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/11 18:50:40 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
int		deal_key(void *key)
{
	write(1, key, 1);
	return (1);
}

int main ()
{
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "42");
	mlx_pixel_put(mlx_ptr, win_ptr, 50, 50, 0xFFFFFF);
	mlx_key_hook(win_ptr, deal_key, (void *)1);
	mlx_loop(mlx_ptr);
	mlx_ptr
	return (0);
}
