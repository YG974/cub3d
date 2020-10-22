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
	t_struct	s;

	if (ac == 2 && ft_suffix(av[1], ".cub") == 1)
		ft_init(av[1], 0, &s);
	else if (ac == 3 && ft_suffix(av[1], ".cub") == 1
			&& ft_strncmp(av[2], "--save", 7) == 0)
		ft_init(av[1], 1, &s);
	else
		ft_putstr_fd("wrong arguments", 2);
	mlx_hook(s.win.ptr, 2, 1L, &ft_key_press, &s);
	mlx_hook(s.win.ptr, 3, 2L, &ft_key_release, &s);
	mlx_hook(s.win.ptr, 17, 1L << 17, &ft_exit, &s);
	mlx_hook(s.win.ptr, 33, 1L << 17, &ft_exit, &s);
	mlx_loop_hook(s.mlx, &ft_key_move, &s);
	mlx_expose_hook(s.win.ptr, &ft_expose, &s);
	mlx_loop(s.mlx);
	return (1);
}

void	ft_init(char *av1, int arg, t_struct *s)
{
	s->cub = ft_strdup(av1);
	s->mlx = mlx_init();
	ft_init_before_parsing_1(s);
	ft_init_before_parsing_2(s);
	ft_parse(s);
	ft_init_raycasting_data(s);
	if (arg == 1)
		ft_bitmap(s);
	s->win.ptr = mlx_new_window(s->mlx, s->win.x, s->win.y, WIN_NAME);
	/*ft_wall(s);*/
	ft_expose(s);
	/*ft_move_forward(s, 0);*/
	/*ft_move_side(s, 0);*/
	/*ft_rotate(s, 0);*/
	/*ft_event(s);*/
	/*mlx_hook(s.win.ptr, 2, 1L, &ft_key_press, &s);*/
	/*mlx_hook(s.win.ptr, 3, 2L, &ft_key_release, &s);*/
	/*mlx_hook(s.win.ptr, 17, 1L << 17, &ft_exit, &s);*/
	/*mlx_hook(s.win.ptr, 33, 1L << 17, &ft_exit, &s);*/
	/*mlx_expose_hook(s.win.ptr, &ft_expose, &s);*/
	/*mlx_loop_hook(s.mlx, &ft_key_move, &s);*/
	/*mlx_loop(s.mlx);*/
	return ;
}

void	ft_event(t_struct *s)
{
	mlx_hook(s->win.ptr, 2, 1L, &ft_key_press, &s);
	mlx_hook(s->win.ptr, 3, 2L, &ft_key_release, &s);
	mlx_hook(s->win.ptr, 17, 1L << 17, &ft_exit, &s);
	mlx_hook(s->win.ptr, 33, 1L << 17, &ft_exit, &s);
	mlx_expose_hook(s->win.ptr, &ft_expose, &s);
	mlx_loop_hook(s->mlx, &ft_key_move, &s);
	mlx_loop(s->mlx);
	return ;
}

void	ft_init_before_parsing_1(t_struct *s)
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
	s->ptr[0] = 0;
	s->ptr[1] = 0;
	s->ptr[2] = 0;
	s->ptr[3] = 0;
	s->ptr[4] = 0;
}

void	ft_init_before_parsing_2(t_struct *s)
{
	s->map.x = 0;
	s->map.y = 0;
	s->map.sprite_nb = 0;
	s->map.tab = 0;
	if (!(s->map.tab = ft_calloc(sizeof(char *), 2)))
		ft_error(s, 1);
	s->cam = 0.0;
	s->p.pos.x = 0.0;
	s->p.pos.y = 0.0;
	s->p.dir.x = 0.0;
	s->p.dir.y = 0.0;
	s->p.plane.x = 0.0;
	s->p.plane.y = 0.0;
	s->p.key.esc = 0;
	s->p.key.w = 0;
	s->p.key.a = 0;
	s->p.key.s = 0;
	s->p.key.d = 0;
	s->p.key.left = 0;
	s->p.key.right = 0;
	s->parse.tex = 0;
	s->parse.color = 0;
	s->parse.res = 0;
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
		ft_error(s, 1);
}
