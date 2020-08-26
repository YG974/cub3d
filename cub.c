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
		ft_init_struct(av[1]);
	else
		return (0);
	return (1);
}

int		ft_is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

void	ft_skip_space(t_struct *s, char *line)
{
	/*printf("%s\n", line);*/
	while (ft_is_space(line[s->i]) == 1)
		s->i++;
	return;
}

void	ft_parse(t_struct *s)
{
	char	*line;
	int		fd;
	int		ret;

	if (!(fd = open(s->cub, O_RDONLY)))
		return ;
	ret = 1;
	if (!(s->map.tab = ft_calloc(sizeof(char **), 1)))
		return ;
	while (ret == get_next_line(fd, &line))
	{
		s->i = 0;
		/*tmp = ft_split(line, ' ');*/
		ft_read_line(s, line);
		free(line);
			/*ft_check_parsing(s);*/
			/*s->map.tab = new_tab(s->map.tab, line);*/
	}
	/*ft_get_pos(s);*/
	while(1);
	close(fd);
}

void	ft_read_line(t_struct *s, char *line)
{
	ft_skip_space(s, line);	
	if (line[s->i] == 'R' && line[s->i + 1] == ' ')
		ft_resolution(s, &line[s->i]);
	if (line[s->i] == 'N' && line[s->i + 1] == 'O' && line[s->i + 2] == ' ')
		s->tex.n = ft_load_tex(s, &line[s->i]);
	if (line[s->i] == 'S' && line[s->i + 1] == 'O' && line[s->i + 2] == ' ')
		s->tex.s = ft_load_tex(s, &line[s->i]);
	if (line[s->i] == 'W' && line[s->i + 1] == 'E' && line[s->i + 2] == ' ')
		s->tex.w = ft_load_tex(s, &line[s->i]);
	if (line[s->i] == 'E' && line[s->i + 1] == 'A' && line[s->i + 2] == ' ')
		s->tex.e = ft_load_tex(s, &line[s->i]);
	if (line[s->i] == 'S' && line[s->i + 1] == ' ')
		s->tex.sprite = ft_load_tex(s, &line[s->i]);
	if (line[s->i] == 'F' && line[s->i + 1] == ' ')
		s->floor = ft_color(s, &line[s->i]);
	if (line[s->i] == 'C' && line[s->i + 1] == ' ')
		s->sky = ft_color(s, &line[s->i]);
	return;
}

void	ft_check_parsing(t_struct *s)
{
	if ((s->win.x == 0 || s->win.y == 0 || s->tex.n == NULL ||
				s->tex.s == NULL || s->tex.w == NULL ||
				s->tex.e == NULL || s->tex.sprite == NULL ||
				s->floor.r == -1 || s->floor.g == -1 || s->floor.b == -1 ||
				s->sky.r == -1 || s->sky.g == -1 || s->sky.b == -1))
		ft_error(1);
}

t_color	ft_color(t_struct *s, char *line)
{
	t_color color;
	char	**tab;
	int		i;

	i = 0;
	s->i = 1;
	tab = ft_split(&line[s->i], ',');
	while (tab[i])
		i++;
	if (i != 3)
		ft_error(1);
	color.r = ft_atoi((const char *)tab[0]);
	color.g = ft_atoi((const char *)tab[1]);
	color.b = ft_atoi((const char *)tab[2]);
	if (color.r > 255 || color.r < 0 ||
			color.g > 255 || color.g < 0 ||
			color.b > 255 || color.b < 0)
		ft_error(1);
	free(tab[0]);
	free(tab[1]);
	free(tab[2]);
	free(tab);
	return (color);
}

void	ft_resolution(t_struct *s, char *line)
{
	char	**tab;
	int		i;

	i = 0;
	s->i++;
	tab = ft_split(&line[s->i], ' ');
	while (tab[i])
		i++;
	if (i != 2)
		ft_error(1);
	s->win.x = ft_atoi((const char *)tab[0]);
	s->win.y = ft_atoi((const char *)tab[1]);
	s->win.x = (s->win.x <= 0 ? WIDTH : s->win.x);
	s->win.x = (s->win.x > WIDTH ? WIDTH : s->win.x);
	s->win.y = (s->win.y <= 0 ? HEIGHT : s->win.y);
	s->win.y = (s->win.y > HEIGHT ? HEIGHT : s->win.y);
	free(tab[0]);
	free(tab[1]);
	free(tab);
	/*ft_init_mlx(s);*/
}

void	ft_error(int i)
{
	write(1, "error\n", 6);
}

int		ft_suffix(char *file_name, char *suffix)
{
	int		i;

	i = ft_strlen(file_name);
	if (file_name[i - 1] == suffix[3] && file_name[i - 2] == suffix[2] &&
			file_name[i - 3] == suffix[1] && file_name[i - 4] == suffix[0] && i > 4)
		return (1);
	else
		write(1, "wrong argument", 14);
	return (0);
}

void	ft_get_pos(t_struct *s)
{
	while (s->map.tab[s->map.y])
	{
		s->map.x = 0;
		while (s->map.tab[s->map.y][s->map.x])
		{
			if (s->map.tab[s->map.y][s->map.x] == 'N')
				s->p.dir.y = -1;
			if (s->map.tab[s->map.y][s->map.x] == 'S')
				s->p.dir.y = 1;
			s->p.plane.x = 0.60 * -s->p.dir.y;
			if (s->map.tab[s->map.y][s->map.x] == 'E')
				s->p.dir.x = 1;
			if (s->map.tab[s->map.y][s->map.x] == 'W')
				s->p.dir.x = -1;
			s->p.plane.y = 0.60 * -s->p.dir.x;
			if ((s->p.dir.x != 0 || s->p.dir.y != 0) && (s->p.pos.x == 0))
			{
				s->map.tab[s->map.y][s->map.x] = '0';
				s->p.pos.x = (double)s->map.x + 0.5;
				s->p.pos.y = (double)s->map.y + 0.5;
			}
			s->map.x++;
		}
		s->map.y++;
	}
}

char	**new_tab(char **tab, char *str)
{
	char	**new_tab;
	int		n;

	n = 0;
	while (tab[n])
		n++;
	if (!(new_tab = ft_calloc(sizeof(char **), n + 2)))
		return (NULL);
	n = 0;
	while (tab[n])
	{
		new_tab[n] = tab[n];
		n++;
	}
	free(tab);
	new_tab[n] = str;
	new_tab[n + 1] = NULL;
	return (new_tab);
}

int		key_press(int key, t_struct *s)
{
	if (key == ESC)
		ft_exit(s);
	else if (key == KEY_A)
		ft_move_side(s, -1);
	else if (key == KEY_S)
		ft_move_forward(s, -1);
	else if (key == KEY_D)
		ft_move_side(s, 1);
	else if (key == KEY_W)
		ft_move_forward(s, 1);	
	else if (key == KEY_LEFT)
		ft_rotate(s, -1);
	else if (key == KEY_RIGHT)
		ft_rotate(s, 1);
	return (1);
}

void	ft_move_forward(t_struct *s, double sign)
{
	/*int	x;*/
	/*int y;*/

	/*x = (int)(s->p.pos.x + sign * s->p.dir.x * SPEED);*/
	/*y = (int)(s->p.pos.y + sign * s->p.dir.y * SPEED);*/
	if (s->map.tab[(int)(s->p.pos.y)]
			[(int)(s->p.pos.x + sign * s->p.dir.x * SPEED)] == '0')
		s->p.pos.x += sign * s->p.dir.x * SPEED;
	if (s->map.tab[(int)(s->p.pos.y + sign * s->p.dir.y * SPEED)]
			[(int)s->p.pos.x] == '0')
		s->p.pos.y += sign * s->p.dir.y * SPEED;
	/*printf("x: %d | y: %d | c: %c\n", x, y, s->map.tab[y][x]);*/
	ft_draw_wall(s);
	mlx_put_image_to_window(s->mlx, s->win.ptr, s->img.ptr, 0, 0);
}

void	ft_move_side(t_struct *s, double sign)
{
	if (s->map.tab[(int)(s->p.pos.y)]
			[(int)(s->p.pos.x + sign * -s->p.dir.y * SPEED)] == '0')
		s->p.pos.x += sign * -s->p.dir.y * SPEED;
	if (s->map.tab[(int)(s->p.pos.y + sign * s->p.dir.x * SPEED)]
			[(int)s->p.pos.x] == '0')
		s->p.pos.y += sign * s->p.dir.x * SPEED;
	ft_draw_wall(s);
	mlx_put_image_to_window(s->mlx, s->win.ptr, s->img.ptr, 0, 0);
}

void	ft_rotate(t_struct *s, double sign)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	rot = ANGLE * sign;
	old_dir_x = s->p.dir.x;
	old_plane_x = s->p.plane.x;
	s->p.dir.x = s->p.dir.x  * cos(rot) - s->p.dir.y * sin(rot);
	s->p.dir.y = old_dir_x * sin(rot) + s->p.dir.y * cos(rot);
	s->p.plane.x = s->p.plane.x * cos(rot) - s->p.plane.y  * sin(rot);
	s->p.plane.y = old_plane_x * sin(rot) + s->p.plane.y  * cos(rot);
	ft_draw_wall(s);
	mlx_put_image_to_window(s->mlx, s->win.ptr, s->img.ptr, 0, 0);
}

void	ft_init_struct(char *av)
{
	t_struct	s;

	s.cub = (char *)ft_strdup(av);
	ft_init_tex(&s);
	ft_init_color(&s);
	ft_init_map(&s);
	ft_init_pos(&s);
	s.mlx = NULL;
	s.mlx = mlx_init();
	s.win.ptr = NULL;
	s.img.adr = 0;
	s.img.ptr = NULL;
	s.win.x = 0;
	s.win.y = 0;
	ft_parse(&s);
	if (!(s.wall.buf = calloc(sizeof(double), s.win.x + 1)))
		return (ft_error(-1));
	/*ft_draw_wall(&s);*/
	ft_print_arg(&s);
	/*mlx_put_image_to_window(s.mlx, s.win.ptr, s.img.ptr, 0, 0);*/
	/*mlx_hook(s.win.ptr, KEY_PRESS, KEY_PRESS_MASK, key_press, &s);*/
	/*mlx_loop(s.mlx);*/
	exit(0);
	return;
}

void	ft_init_pos(t_struct *s)
{
	s->p.pos.x = 0.0;
	s->p.pos.y = 0.0;
	s->p.dir.x = 0.0;
	s->p.dir.y = 0.0;
	s->p.plane.x = 0.0;
	s->p.plane.y = 0.0;
	s->cam = 0.0;
	s->ray.dir = s->p.plane;
	s->ray.sd = s->p.plane;
	s->ray.dd = s->p.plane;
	s->wall.step.x = 0;
	s->wall.step.y = 0;
	s->wall.side = 0;
	s->wall.hit = 0;
	s->ray.pos = s->wall.step;
}

void	ft_init_map(t_struct *s)
{
	s->map.tab = NULL;
	s->map.x = 0;
	s->map.y = 0;
	s->map.sprite_nb = 0;
}

void	ft_init_color(t_struct *s)
{
	s->sky.r = -1;
	s->sky.g = -1;
	s->sky.b = -1;
	s->floor = s->sky;
	return ;
}

void	ft_init_tex(t_struct *s)
{
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
}

void	ft_init_mlx(t_struct *s)
{
	int tab[3];

	s->win.ptr = mlx_new_window(s->mlx, s->win.x, s->win.y, "42");
	s->img.ptr = mlx_new_image(s->mlx, s->win.x, s->win.y);
	s->img.adr = (unsigned int*)mlx_get_data_addr(s->img.ptr, 
			&tab[0], &tab[1],&tab[2]);
	/*ft_move_forward(s, 1);*/
	/*ft_move_forward(s, -1);*/
	/*ft_move_side(s, -1);*/
	/*ft_move_side(s, 1);*/
	/*ft_rotate(s, -1);*/
	/*ft_rotate(s, 1);*/
	return ;
}



void	ft_draw_wall(t_struct *s)
{
	s->x = 0;
	while (s->x < s->win.x)
	{
		ft_ray_init(s);
		ft_ray_direction(s);
		ft_ray_hit(s);
		ft_coloumn_size(s);
		ft_column_texture(s);
		ft_draw_columns(s);
		s->x++;
	}
	ft_sprite(s);
}

void	print_sprite(t_struct *s)
{
		printf("sprite N:%d | ", s->i);
		printf("WallDst = %6.2f | ", s->wall.buf[(s->win.x / 2)]);
		printf("spr Dst = %6.2f | ", s->sprite[s->i].dist);
		printf("d x  = %6.2f | ", s->sprite[s->i].delta.x);
		printf("d y  = %6.2f | ", s->sprite[s->i].delta.y);
		printf("height = %d | ", s->sprite[s->i].height);
		printf("depth x  = %6.2f | ", s->sprite[s->i].depth.x);
		printf("depth y  = %6.2f | ", s->sprite[s->i].depth.y);
		printf("start x = %d | ", s->sprite[s->i].start.x);
		printf("start y = %d | ", s->sprite[s->i].start.y);
		printf("end x = %d | ", s->sprite[s->i].end.x);
		printf("end y = %d\n", s->sprite[s->i].end.y);

}

void	ft_sprite(t_struct *s)
{
	if ( s->map.sprite_nb == 0)
	{
		ft_count_sprite(s);
	if (!(s->sprite = ft_calloc(sizeof(t_sprite), s->map.sprite_nb)))
		return (ft_error(-1));
	}
	ft_sprite_pos(s);
	ft_sprite_distance(s);
	ft_sort_sprite(s);
	s->i = 0;
	printf("\n");
	while (s->i < s->map.sprite_nb)
	{
		ft_sprite_transform(s);
		ft_sprite_size(s);
		ft_draw_sprite(s);
		/*print_sprite(s);*/
		s->i++;
	}
}

/* inv = coef to inverse Matrice */
void	ft_sprite_transform(t_struct *s)
{
	double	inv;

	inv = 0.0;
	s->sprite[s->i].delta.x = s->sprite[s->i].pos.x - s->p.pos.x;
	s->sprite[s->i].delta.y = s->sprite[s->i].pos.y - s->p.pos.y;
	inv = 1.0 / (s->p.plane.x * s->p.dir.y - s->p.plane.y * s->p.dir.x);
	s->sprite[s->i].depth.x = inv * (s->p.dir.y  * s->sprite[s->i].delta.x 
			- s->p.dir.x * s->sprite[s->i].delta.y);
	s->sprite[s->i].depth.y = inv * (s->p.plane.x  * s->sprite[s->i].delta.y -
			s->p.plane.y  * s->sprite[s->i].delta.x);
	s->sprite[s->i].screen = (int)((s->win.x / 2) * 
		(1 + s->sprite[s->i].depth.x / s->sprite[s->i].depth.y));
}

void	ft_sprite_size(t_struct *s)
{
	s->sprite[s->i].height = abs((int)(s->win.y / s->sprite[s->i].depth.y));
	s->sprite[s->i].start.y = (s->win.y / 2) - (s->sprite[s->i].height / 2);
	if (s->sprite[s->i].start.y < 0)
		s->sprite[s->i].start.y = 0;
	s->sprite[s->i].end.y = (s->win.y / 2) + (s->sprite[s->i].height / 2);
	if (s->sprite[s->i].end.y >= s->win.y)
		s->sprite[s->i].end.y = s->win.y - 1;
	s->sprite[s->i].width = abs((int)(s->win.y / s->sprite[s->i].depth.y));
	s->sprite[s->i].start.x = s->sprite[s->i].screen - (s->sprite[s->i].width / 2);
	if (s->sprite[s->i].start.x < 0)
		s->sprite[s->i].start.x = 0;
	s->sprite[s->i].end.x = s->sprite[s->i].screen + s->sprite[s->i].width / 2;
	if (s->sprite[s->i].end.x >= s->win.x)
		s->sprite[s->i].end.x = s->win.x - 1;
}

void	ft_draw_sprite(t_struct *s)
{
	int	x;
	int	y;
	int	d;

	x = s->sprite[s->i].start.x;
	while (x < s->sprite[s->i].end.x)
	{
		s->tex.x = (int)(256 * (x - (-s->sprite[s->i].width / 2 + s->sprite[s->i].screen)) *
			64 / s->sprite[s->i].width) / 256;
		y = s->sprite[s->i].start.y;
		while (y < s->sprite[s->i].end.y)
		{
			/*s->tex.y = (int)(((y + s->sprite[s->i].width / 2 - s->sprite[s->i].screen)) **/
				/*s->tex.width / s->sprite[s->i].width);*/
			d = y * 256 - s->win.y * 128 + s->sprite[s->i].height * 128;
			s->tex.y = (int)((d * 64) / s->sprite[s->i].height) / 256;
			if (x > 0 && x < s->win.x && s->sprite[s->i].depth.y > 0 &&
					s->sprite[s->i].depth.y < s->wall.buf[x])
			{
				s->color = s->tex.sprite[64 * s->tex.y + s->tex.x];
				if (s->color != BLACK) 
					s->img.adr[x + s->win.x * y] = s->color;
			}
			y++;
		}
		x++;
	}
}

void	ft_pixel_sprite(t_struct *s)
{
}
void	ft_sprite_distance(t_struct *s)
{
	int i;

	i = 0;
	while (i < s->map.sprite_nb)
	{
		s->sprite[i].dist = hypot(s->p.pos.x - s->sprite[i].pos.x,
				s->p.pos.y - s->sprite[i].pos.y);
		i++;
	}
}

void	ft_sort_sprite(t_struct *s)
{
	int i;
	int	j;
	t_sprite	tmp;

	i = 0;
	while (i < s->map.sprite_nb - 1)
	{
		j = i + 1;
		while (j < s->map.sprite_nb)
		{
			if (s->sprite[i].dist < s->sprite[j].dist )
			{
				tmp = s->sprite[i];
				s->sprite[i] = s->sprite[j] ;
				s->sprite[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_sprite_pos(t_struct *s)
{
	int	i;

	i = 0;
	while (i < s->map.sprite_nb)
	{
		s->y = 0;
		while (s->map.tab[s->y]) 
		{
			s->x = 0;
			while(s->map.tab[s->y][s->x])
			{
				if (s->map.tab[s->y][s->x] == '2')
				{
					s->sprite[i].pos.x = s->x + 0.5;
					s->sprite[i].pos.y = s->y + 0.5;
					i++;
				}
				s->x++;
			}
			s->y++;
		}
	}
}

void	ft_count_sprite(t_struct *s)
{
	s->y = 0;
	while (s->map.tab[s->y]) 
	{
		s->x = 0;
		while(s->map.tab[s->y][s->x])
		{
			if (s->map.tab[s->y][s->x] == '2')
				s->map.sprite_nb++;
			s->x++;
		}
		s->y++;
	}
}

void	ft_ray_init(t_struct *s)
{
	s->cam = 2 * s->x / (double)(s->win.x) - 1;
	s->ray.dir.x = s->p.dir.x + s->p.plane.x * s->cam;
	s->ray.dir.y = s->p.dir.y + s->p.plane.y * s->cam;
	s->ray.dd.x = sqrt(1 + pow(s->ray.dir.y, 2) / pow(s->ray.dir.x, 2));
	s->ray.dd.y = sqrt(1 + pow(s->ray.dir.x, 2) / pow(s->ray.dir.y, 2));
	s->ray.pos.x = (int)s->p.pos.x;
	s->ray.pos.y = (int)s->p.pos.y;
	s->wall.hit = 0;
}

void	ft_ray_direction(t_struct *s)
{
	if (s->ray.dir.x < 0)
	{
		s->wall.step.x = -1;
		s->ray.sd.x = (s->p.pos.x - s->ray.pos.x) * s->ray.dd.x;
	}
	else
	{
		s->wall.step.x = 1;
		s->ray.sd.x = (s->ray.pos.x + 1.0 - s->p.pos.x) * s->ray.dd.x;
	}
	if (s->ray.dir.y < 0)
	{
		s->wall.step.y = -1;
		s->ray.sd.y = (s->p.pos.y - s->ray.pos.y) * s->ray.dd.y;
	}
	else
	{
		s->wall.step.y = 1;
		s->ray.sd.y = (s->ray.pos.y + 1.0 - s->p.pos.y) * s->ray.dd.y;
	}
}

void	ft_ray_hit(t_struct *s)
{
	while (s->wall.hit == 0)
	{
		if (s->ray.sd.x < s->ray.sd.y)
		{
			s->ray.sd.x += s->ray.dd.x;
			s->ray.pos.x += s->wall.step.x;
			s->wall.side = 0;
		}
		else
		{
			s->ray.sd.y += s->ray.dd.y;
			s->ray.pos.y += s->wall.step.y;
			s->wall.side = 1;
		}
		if (s->map.tab[s->ray.pos.y][s->ray.pos.x] == '1')
			s->wall.hit = 1;
	}

}

void	ft_coloumn_size(t_struct *s)
{
	if (s->wall.side == 0)
		s->wall.perp_dist = fabs((s->ray.pos.x - s->p.pos.x + 
					(1 - s->wall.step.x) / 2) / s->ray.dir.x);
	else
		s->wall.perp_dist = fabs((s->ray.pos.y - s->p.pos.y + 
					(1 - s->wall.step.y) / 2) / s->ray.dir.y);
	s->wall.buf[s->x] = s->wall.perp_dist;
	s->wall.height = (int)(s->win.y / s->wall.perp_dist);
	s->wall.start = -s->wall.height / 2 + s->win.y / 2;
	s->wall.start = (s->wall.start > 0 ? s->wall.start : 0);
	s->wall.end = s->wall.height / 2 + s->win.y / 2;
	s->wall.end = (s->wall.end >= s->win.y ? s->win.y - 1 : s->wall.end);
	if (s->wall.side == 0)
		s->wall.x = s->p.pos.y + s->wall.perp_dist * s->ray.dir.y;
	else
		s->wall.x = s->p.pos.x + s->wall.perp_dist * s->ray.dir.x;
	s->wall.x -= floor(s->wall.x);
}
/* remplacer les 64 par texture_width) */
void	ft_column_texture(t_struct *s)
{
	s->tex.x = (int)(s->wall.x * 64);
	if (s->wall.side == 0 && s->ray.dir.x > 0)
		s->tex.x = 64 - s->tex.x - 1;
	if (s->wall.side == 1 && s->ray.dir.y < 0)
		s->tex.x = 64 - s->tex.x - 1;
	s->tex.step = (double)64 / s->wall.height;
	s->tex.pos = (s->wall.start - s->win.y / 2 + s->wall.height / 2)
		* s->tex.step;
}

void	ft_draw_columns(t_struct *s)
{
	s->color = s->sky.r * 256 * 256 + s->sky.g * 256 + s->sky.b;
	s->y = 0;
	while (s->y < s->wall.start)
			s->img.adr[s->x + s->win.x * s->y++] = s->color;
	while (s->y >= s->wall.start && s->y <= s->wall.end)
	{
	s->tex.y = (int)s->tex.pos /*& (64 - 1)*/;
	s->tex.pos += s->tex.step;
		ft_pixel(s);
		/*mlx_pixel_put(s->mlx, s->win.ptr, s->x, s->y, s->color);*/
		s->y++;
	}
	s->color = s->floor.r * 256 * 256 + s->floor.g * 256 + s->floor.b;
	while (s->y < s->win.y)
			s->img.adr[s->x + s->win.x * s->y++] = s->color;
}

void	ft_pixel(t_struct *s)
{
	int	pix_nb;

	pix_nb = 64 * s->tex.y + s->tex.x; 
	if (s->wall.side == 0)
	{
		if (s->wall.step.x < 0)
			s->img.adr[s->x + s->win.x * s->y] = s->tex.w[pix_nb];
		else
			s->img.adr[s->x + s->win.x * s->y] = s->tex.e[pix_nb];
	}
	else
	{
		if (s->wall.step.y < 0)
			s->img.adr[s->x + s->win.x * s->y] = s->tex.n[pix_nb];
		else
			s->img.adr[s->x + s->win.x * s->y] = s->tex.s[pix_nb];
	}
}

unsigned int	*ft_load_tex(t_struct *s, char *line)
{
	void	*ptr;
	int		tmp[5];
	unsigned int	*adr;
	int		fd;
	char	**tab;
	int		i;

	i = 0;
	s->i += 2;
	tab = ft_split(&line[s->i], ' ');
	while (tab[i])
		i++;
	if (i != 1)
		ft_error(1);
	ptr = mlx_xpm_file_to_image(s->mlx, tab[0], &tmp[0], &tmp[1]);
	if (tmp[0] != tmp[1])
		return (NULL);
	s->tex.width = tmp[0];
	adr = (unsigned int*)mlx_get_data_addr(ptr, &tmp[2], &tmp[3], &tmp[4]);
	free(ptr);
	free(tab[0]);
	free(tab);
	return (adr);
}

void	ft_print_arg(t_struct *s)
{
	printf("RESOLUTION : %d x %d\n", s->win.x, s->win.y);
	printf("FLOOR : %d,%d,%d\n", s->floor.r, s->floor.g, s->floor.b);
	printf("SKY : %d,%d,%d\n", s->sky.r, s->sky.g, s->sky.b);
	print_map(s);
	printf("MAP : %dx%d\n", s->map.x, s->map.y);
	printf("POS : [%.f,%.f]\n", s->p.pos.x, s->p.pos.y);
	printf("DIR : %.f, %.f\n", s->p.dir.x, s->p.dir.y);
	printf("texture width : %d\n", s->tex.width);
	printf("texture N : %p\n", s->tex.n);
	printf("texture s : %p\n", s->tex.s);
	printf("texture e : %p\n", s->tex.e);
	printf("texture w : %p\n", s->tex.w);
	printf("texture S : %p\n", s->tex.sprite);
	printf("nb sprite: %d\n", s->map.sprite_nb);
}

void	print_map(t_struct *s)
{
	int i;

	i = 0;
	while (s->map.tab[i])
	{
		printf("%s\n", s->map.tab[i]);
		i++;
	}
}

int		ft_exit(t_struct *s)
{
	exit(0);
	return (1);
}
