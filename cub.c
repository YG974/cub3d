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
		if (ac == 2 && ft_suffix(av[1], ".cub") == 1)
			ft_init_struct(av[1]);
		else
				return (0);
		return (0);
}

void	ft_parse(t_struct	*s)
{
	int		fd;
	char	*file;
	
}

int		ft_suffix(char *file_name, char *suffix)
{
	int		i;

	i = strlen(file_name);
	if (file_name[i - 1] == suffix[3] && file_name[i - 2] == suffix[2] && 
	file_name[i - 3] == suffix[1] && file_name[i - 4] == suffix[0] && i > 4)
		return (1);
	else
		write(1, "wrong argument", 14);
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


void	ft_init_struct(char	*av)
{
		t_struct	s;
		
		s.cub = strdup(av);
		ft_init_tex(&s);
		ft_init_color(&s);
		ft_init_map(&s);
		s.mlx = NULL;
		s.win = NULL;
		s.win_x = 0;
		s.win_y = 0;
		s.x = 0;
		s.y	= 0;
	//	ft_parse(&s);
		ft_init_mlx(&s);
}

void	ft_init_map(t_struct *s)
{
		s->map.tab = NULL;
		s->map.x = 0;
		s->map.y = 0;
}

void	ft_init_color(t_struct *s)
{
	s->sky.R = 0;
	s->sky.G = 0;
	s->sky.B = 0;
	s->floor = s->sky;
	return;
}

void	ft_init_tex(t_struct *s)
{
	s->tex.N.path = NULL;
	s->tex.N.adr = NULL;
	s->tex.N.x = 0;
	s->tex.N.y = 0;
	s->tex.N.endian = 0;
	s->tex.N.bpp = 0;
	s->tex.N.sl = 0;
	s->tex.S = s->tex.N;
	s->tex.E = s->tex.N;
	s->tex.W = s->tex.N;
	s->tex.sprite = s->tex.N;
}

void	ft_init_mlx(t_struct *s)
{
		s->mlx = mlx_init();
		s->win_x = WIDTH;
		s->win_y = HEIGHT;
		s->win = mlx_new_window(s->mlx, s->win_x, s->win_y, "42");
		mlx_hook(s->win, KEY_PRESS, KEY_PRESS_MASK, key_press, s);
		ft_img_adr(s);
		mlx_loop(s->mlx);
		return;	
}

void	ft_img_adr(t_struct *s)
{
		int		bpp;
		int		sl;
		int		end;
		char	*file;

		file = strdup("./images/wood.xpm");
	//	printf("%d\n", s->tex.N.x);
	s->tex.N.adr = mlx_xpm_file_to_image(s->mlx, file, &s->tex.N.x, &s->tex.N.y);
   mlx_put_image_to_window(s->mlx, s->win, s->tex.N.adr, 0, 0);
}

int		ft_exit(t_struct *s)
{
		exit(0);
		return(1);
}
