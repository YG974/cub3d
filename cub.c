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

int main (int ac, char **av)
{
		if (ac == 2)
			ft_start(av[1]);
		else
				return (0);
		return (0);
}

int		key_press(int key, t_struct *s)
{
		if (key == ESC)
				ft_exit(s);
		else if (key == KEY_A)
				write(1, "A", 1);
		else if (key == KEY_S)
				write(1, "S", 1);
		else if (key == KEY_D)
				write(1, "D", 1);
		else if (key == KEY_W)
				write(1, "W", 1);
		return (1);
}


void	ft_init_struct(void)
{
		t_struct	s;

		s.mlx_ptr = 0;
		s.win_ptr = 0;
		s.win_x = 0;
		s.win_y = 0;
		s.x = 0;
		s.y = 0;
		ft_init_mlx(&s);
}

void	ft_init_mlx(t_struct *s)
{
		s->mlx_ptr = mlx_init();
		s->win_x = WIDTH;
		s->win_y = HEIGHT;
		s->win_ptr = mlx_new_window(s->mlx_ptr, s->win_x, s->win_y, "42");
		mlx_hook(s->win_ptr, KEY_PRESS, KEY_PRESS_MASK, key_press, s);
		ft_img_adr(s);
		mlx_loop(s->mlx_ptr);
		return ;	
}

void	ft_img_adr(t_struct *s)
{
		int		bpp;
		int		sl;
		int		end;
		char	*file;

		file = strdup(PATH_WOOD);
	//	printf("%s\n", file);
	s->img_ptr = mlx_xpm_file_to_image(s->mlx_ptr, file, &s->img_x, &s->img_y);
   mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img_ptr, 0, 0);
}

int		ft_exit(t_struct *s)
{
		exit(0);
		return(1);
}
