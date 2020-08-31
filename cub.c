/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:07 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		main(int ac, char **av)
{
	if (ac == 2 && ft_suffix(av[1], ".cub") == 1)
		ft_init(av[1], 0);
	else if (ac == 3 && ft_suffix(av[1], ".cub") == 1 
			&& ft_strncmp(av[2], "--save", 7) == 0)
		ft_init(av[1], 1);
	else
		write(2, "wrong arguments", 15);
	return (1);
}
void	ft_event(t_struct *s)
{
}

void	ft_init(char *av1, int arg)
{
	t_struct	s;
	int tab[3];

	if (!(s.map.tab= ft_calloc(sizeof(char **), 1)))
	{
		write(2, "Error : calloc fail\n", 20);
		return ;
	}
	s.cub = ft_strdup(av1);
	s.mlx = mlx_init();
	ft_init_file_data(&s);
	ft_init_player(&s);
	ft_parse(&s);
	ft_init_raycasting_data(&s);
	s.img.ptr = mlx_new_image(s.mlx, s.win.x, s.win.y);
	s.img.adr = (unsigned int*)mlx_get_data_addr(s.img.ptr, 
			&tab[0], &tab[1],&tab[2]);
	if (arg == 1)
		ft_bitmap(&s);
	s.win.ptr = mlx_new_window(s.mlx, s.win.x, s.win.y, WIN_NAME);
	/*ft_print_arg(&s);*/
	print_map(&s);
	/*mlx_put_image_to_window(s.mlx, s.win.ptr, s.img.ptr, 0, 0);*/
	ft_wall(&s);
	mlx_put_image_to_window(s.mlx, s.win.ptr, s.img.ptr, 0, 0);
	mlx_hook(s.win.ptr, KEY_PRESS, KEY_PRESS_MASK, key_press, &s);
	/*mlx_hook(s.win.ptr, KEY_RELEASE, KEY_RELEASE_MASK, key_press, &s);*/
	mlx_loop(s.mlx);
	exit(0); 
	return;
}


void	ft_init_file_data(t_struct *s)
{
	s->win.ptr = 0;
	s->win.x = 0;
	s->win.y = 0;
	s->img.ptr = 0;
	s->img.adr = 0;
	s->tex.n = 0;
	s->tex.s = 0;
	s->tex.e = 0;
	s->tex.w = 0;
	s->tex.sprite = 0;
	s->tex.pos = 0.0;
	s->tex.step = 0.0;
	s->tex.x = 0;
	s->tex.y = 0;
	s->tex.width = 0;
	s->sky.r = -1;
	s->sky.g = -1;
	s->sky.b = -1;
	s->sky.color = 0;
	s->floor = s->sky;
	s->map.x = 0;
	s->map.y = 0;
	s->map.sprite_nb = 0;
}

void	ft_init_player(t_struct *s)
{
	s->cam = 0.0;
	s->p.pos.x = 0.0;
	s->p.pos.y = 0.0;
	s->p.dir.x = 0.0;
	s->p.dir.y = 0.0;
	s->p.plane.x = 0.0;
	s->p.plane.y = 0.0;
}

void	ft_init_raycasting_data(t_struct *s)
{
	s->ray.pos.x = 0;
	s->ray.pos.y = 0;
	s->ray.dir = s->p.plane;
	s->ray.sd = s->p.plane;
	s->ray.dd = s->p.plane;
	s->wall.step = s->ray.pos;
	s->wall.side = 0;
	s->wall.hit = 0;
	s->wall.height = 0;
	s->wall.start = 0;
	s->wall.end = 0;
	s->wall.perp_dist = 0.0;
	s->wall.x = 0.0;
	if (!(s->wall.buf = ft_calloc(sizeof(double), s->win.x + 1)))
	{
		write(2, "Error : calloc fail\n", 20);
		return ;
	}
}

int		ft_exit(t_struct *s)
{
	exit(0);
	return (1);
}
