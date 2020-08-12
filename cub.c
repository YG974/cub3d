/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                             :+:      :+:    :+:   */
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
	return (1);
}

void	ft_parse(t_struct	*s)
{
	char	**line;
	int		fd;
	int		ret;

	line = &s->buf;
	if (!(fd = open(s->cub, O_RDONLY)))
		return ;	
	ret = 1;
	s->i = 0;
	if (!(s->map.tab = calloc(sizeof(char **), 1)))
		return ;
	while (ret == get_next_line(fd, line))		
	{
		s->tmp = ft_split(s->buf, ' ');
		ft_read_line(s);
		if (s->tmp[0] && s->tmp[0][0] && s->tmp[0][0] == '1')
		{
			ft_check_parsing(s);
			s->map.tab = new_tab(s->map.tab, s->buf);
		}
	}
	ft_get_pos(s);
	close(fd);
}

void	ft_get_pos(t_struct *s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s->map.tab[s->map.y])
		s->map.y++;
	while (j < s->map.y)
	{
		while (s->map.tab[j][i])
		{
			if (s->map.tab[j][i] == 'N')
				s->dir.y = 1;
			if (s->map.tab[j][i] == 'S')
				s->dir.y = -1;
			if (s->map.tab[j][i] == 'E')
				s->dir.x = 1;
			if (s->map.tab[j][i] == 'W')
				s->dir.x = -1;
			if ((s->dir.x != 0 || s->dir.y != 0) && (s->pos.x == 0))
			{
				s->pos.x = (double)i;
				s->pos.y = (double)j;
			}
			i++;
			s->map.x = (s->map.x > i ? s->map.x : i);
		}
		i = 0;
		j++;
	}
	return ;
}

void	ft_read_line(t_struct *s)
{		
	int i = 0;
	while (s->tmp[i])
	{
		if (ft_strncmp(s->tmp[0], "R", 1) == 0 && s->tmp[0] != '\0')
			ft_resolution(s);
		if (ft_strncmp(s->tmp[0], "NO", 2) == 0 && s->tmp[0] != '\0')
			s->tex.N.path = ft_strdup(s->tmp[1]);
		if (ft_strncmp(s->tmp[0], "SO", 2) == 0 && s->tmp[0] != '\0')
			s->tex.S.path = ft_strdup(s->tmp[1]);
		if (ft_strncmp(s->tmp[0], "WE", 2) == 0 && s->tmp[0] != '\0')
			s->tex.W.path = ft_strdup(s->tmp[1]);
		if (ft_strncmp(s->tmp[0], "EA", 2) == 0 && s->tmp[0] != '\0')
			s->tex.E.path = ft_strdup(s->tmp[1]);
		if (ft_strncmp(s->tmp[0], "S", 1) == 0 && s->tmp[0] != '\0')
			s->tex.sprite.path = ft_strdup(s->tmp[1]);
		if (ft_strncmp(s->tmp[0], "F", 1) == 0 && s->tmp[0] != '\0')
			s->floor = ft_color(s);;
		if (ft_strncmp(s->tmp[0], "C", 1) == 0 && s->tmp[0] != '\0')
			s->sky = ft_color(s);;
		i++;
	}
}

void	ft_check_parsing(t_struct *s)
{
	if ((s->win_x == 0 || s->win_y == 0 || s->tex.N.path == NULL ||
				s->tex.S.path == NULL || s->tex.W.path == NULL || 
				s->tex.E.path == NULL || s->tex.sprite.path == NULL || 
				s->floor.R == -1 || s->floor.G == -1 || s->floor.B == -1 || 
				s->sky.R == -1 || s->sky.G == -1 || s->sky.B == -1))
		ft_error(1);
}



t_color	ft_color(t_struct	*s)
{
	t_color color;
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split(s->tmp[1], ',');
	while (tab[i])
		i++;
	if (i > 3 || i < 3)
		ft_error(1);
	color.R = ft_atoi((const char *)tab[0]);
	color.G = ft_atoi((const char *)tab[1]);
	color.B = ft_atoi((const char *)tab[2]);
	if (color.R > 255 || color.R < 0 || 
			color.G > 255 || color.G < 0 ||
			color.B > 255 || color.B < 0)
		ft_error(1);
	return (color);
}

void	ft_resolution(t_struct *s)
{
	s->win_x = ft_atoi((const char *)s->tmp[1]);
	s->win_y = ft_atoi((const char *)s->tmp[2]);
	s->win_x = (s->win_x <= 0  ? WIDTH : s->win_x);
	s->win_x = (s->win_x > WIDTH ? WIDTH : s->win_x);
	s->win_y = (s->win_y <= 0 ? HEIGHT : s->win_y);
	s->win_y = (s->win_y > HEIGHT ? HEIGHT : s->win_y);
}

void	ft_error(int i)
{
	write(1, "error\n", 6);
}

void	skip_space(t_struct *s)
{
	while (is_space(s->buf[s->i]))
		s->i++;
}



int		is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' ||
			c == '\v' || c == '\f' || c == ' ')
		return (1);
	else
		return (0);
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

char	**new_tab(char **tab, char *str)
{
	char	**new_tab;
	int		n;

	n = 0;
	while (tab[n])
		n++;
	if (!(new_tab = calloc(sizeof(char **), n + 2)))
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

	s.cub = (char *)ft_strdup(av);
	ft_init_tex(&s);
	ft_init_color(&s);
	ft_init_map(&s);
	ft_init_pos(&s);
	s.mlx = NULL;
	s.win = NULL;
	s.win_x = 0;
	s.win_y = 0;
	ft_parse(&s);
	ft_init_mlx(&s);
}

void	ft_init_pos(t_struct *s)
{
	s->pos.x = 0;
	s->pos.y = 0;
	s->dir.x = 0;
	s->dir.y = 0;
	s->plane.x = 0;
	s->plane.y = 0.66;
	s->cam.x = 0;
	s->cam.y = 0;
	s->ray.x = 0;
	s->ray.y = 0;
	s->side_dist = s->plane;
	s->delta_dist = s->plane;
	s->step.x = 0;
	s->step.y = 0;
	s->side = 0;
	s->hit = 0;
	s->map_pos = s->step;
	s->perp_wall_dist = 0;
}

void	ft_init_map(t_struct *s)
{
	s->map.tab = NULL;
	s->map.x = 0;
	s->map.y = 0;
}

void	ft_init_color(t_struct *s)
{
	s->sky.R = -1;
	s->sky.G = -1;
	s->sky.B = -1;
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
	s->win = mlx_new_window(s->mlx, s->win_x, s->win_y, "42");
	ft_load_tex(s);
	ft_print_arg(s);
	s->ptr = mlx_new_image(s->mlx, s->win_x, s->win_y);
	ft_draw_wall(s);
	mlx_put_image_to_window(s->mlx, s->win, s->tex.S.ptr, 0, 0);
	mlx_hook(s->win, KEY_PRESS, KEY_PRESS_MASK, key_press, s);
	mlx_loop(s->mlx);
	return;	
}

void	ft_draw_wall(t_struct *s)
{
	int x;

	x = 0;
	s->cam.x = 2 * x / (double)(s->win_x) - 1;
	while (x < s->win_x)
	{
		ft_ray_init(s);
		ft_ray_init(s);
		ft_ray_direction(s);
		ft_ray_hit(s);
	}
	
}

void	ft_ray_init(t_struct *s)
{
	s->ray.x = s->dir.x + s->plane.x * s->cam.x;
	s->ray.y = s->dir.y + s->plane.y * s->cam.x;
	s->delta_dist.x = sqrt(1 + pow(s->ray.x, 2) / pow(s->ray.y, 2));
	s->delta_dist.y = sqrt(1 + pow(s->ray.y, 2) / pow(s->ray.y, 2));
	s->map_pos.x = (int)s->pos.x;
	s->map_pos.y = (int)s->pos.y;
}

void	ft_ray_direction(t_struct *s)
{
	if (s->ray.x < 0)
	{
		s->step.x = -1;
		s->side_dist.x = (s->pos.x - s->map_pos.x) * s->delta_dist.x;
	}
	else
	{
		s->step.x = 1;
		s->side_dist.x = (s->map_pos.x + 1 - s->pos.x ) * s->delta_dist.x;
	}
	if (s->ray.y < 0)
	{
		s->step.y = -1;
		s->side_dist.y = (s->pos.y - s->map_pos.y) * s->delta_dist.y;
	}
	else
	{
		s->step.y = 1;
		s->side_dist.y = (s->map_pos.y + 1 - s->pos.y ) * s->delta_dist.y;
	}
}

void	ft_ray_hit(t_struct *s)
{
	while (s->hit == 0)
	{
		if (s->side_dist.x < s->side_dist.y)
		{
			s->side_dist.x += s->delta_dist.x;
			s->map_pos.x += s->step.x;
			s->side = 0;
		}
		else
		{
			s->side_dist.y += s->delta_dist.y;
			s->map_pos.y += s->step.y;
			s->side = 1;
		}
		if (s->map.tab[s->map_pos.x][s->map_pos.y] == 1)
			s->hit = 1;
	}
	if (s->side == 0)
		s->perp_wall_dist = (s->map_pos.x - s->pos.x + (1 - s->step.x)
				/ 2) / s->ray.x;
	else
		s->perp_wall_dist = (s->map_pos.y - s->pos.y + (1 - s->step.y)
				/ 2) / s->ray.y;
}

void	ft_load_tex(t_struct *s)
{
	s->tex.N.ptr = mlx_xpm_file_to_image(s->mlx, s->tex.N.path, 
			&s->tex.N.x, &s->tex.N.y);
	s->tex.S.ptr = mlx_xpm_file_to_image(s->mlx, s->tex.S.path, 
			&s->tex.S.x, &s->tex.S.y);
	s->tex.W.ptr = mlx_xpm_file_to_image(s->mlx, s->tex.W.path, 
			&s->tex.W.x, &s->tex.W.y);
	s->tex.E.ptr = mlx_xpm_file_to_image(s->mlx, s->tex.E.path, 
			&s->tex.E.x, &s->tex.E.y);
	s->tex.sprite.ptr = mlx_xpm_file_to_image(s->mlx, 
			s->tex.sprite.path, &s->tex.sprite.x, &s->tex.sprite.y);
	s->tex.N.adr = (unsigned int*)mlx_get_data_addr(s->tex.N.ptr, 
			&s->tex.N.bpp, &s->tex.N.sl, &s->tex.N.endian);
	s->tex.S.adr = (unsigned int*)mlx_get_data_addr(s->tex.S.ptr, 
			&s->tex.S.bpp, &s->tex.S.sl, &s->tex.S.endian);
	s->tex.W.adr = (unsigned int*)mlx_get_data_addr(s->tex.W.ptr, 
			&s->tex.W.bpp, &s->tex.W.sl, &s->tex.W.endian);
	s->tex.E.adr = (unsigned int*)mlx_get_data_addr(s->tex.E.ptr, 
			&s->tex.E.bpp, &s->tex.E.sl, &s->tex.E.endian);
	s->tex.sprite.adr = (unsigned int*)mlx_get_data_addr(s->tex.sprite.ptr,
			&s->tex.sprite.bpp, &s->tex.sprite.sl, &s->tex.sprite.endian);
	return ;
}
void	ft_print_arg(t_struct *s)
{
	printf("RESOLUTION : %d x %d\n", s->win_x, s->win_y);
	printf("NO_PATH : \"%s\"\n", s->tex.N.path);
	printf("SO_PATH : \"%s\"\n", s->tex.S.path);
	printf("WE_PATH : \"%s\"\n", s->tex.W.path);
	printf("EA_PATH : \"%s\"\n", s->tex.E.path);
	printf("SPRITE_PATH : \"%s\"\n", s->tex.sprite.path);
	printf("FLOOR : %d,%d,%d\n", s->floor.R, s->floor.G, s->floor.B);
	printf("SKY : %d,%d,%d\n", s->sky.R, s->sky.G, s->sky.B);
	print_map(s);
	printf("TEXTURE N\nx:%d | y:%d | adresse:%p | endian:%d | bpp:%d | sizeline:%d\n", s->tex.N.x, s->tex.N.y, s->tex.N.adr, s->tex.N.endian, s->tex.N.bpp, s->tex.N.sl);
	printf("TEXTURE S\nx:%d | y:%d | adresse:%p | endian:%d | bpp:%d | sizeline:%d\n", s->tex.S.x, s->tex.S.y, s->tex.S.adr, s->tex.S.endian, s->tex.S.bpp, s->tex.S.sl);
	printf("TEXTURE W\nx:%d | y:%d | adresse:%p | endian:%d | bpp:%d | sizeline:%d\n", s->tex.W.x, s->tex.W.y, s->tex.W.adr, s->tex.W.endian, s->tex.W.bpp, s->tex.W.sl);
	printf("TEXTURE E\nx:%d | y:%d | adresse:%p | endian:%d | bpp:%d | sizeline:%d\n", s->tex.E.x, s->tex.E.y, s->tex.E.adr, s->tex.E.endian, s->tex.E.bpp, s->tex.E.sl);
	printf("TEXTURE sprite\nx:%d | y:%d | adresse:%p | endian:%d | bpp:%d | sizeline:%d\n", s->tex.sprite.x, s->tex.sprite.y, s->tex.sprite.adr, s->tex.sprite.endian, s->tex.sprite.bpp, s->tex.sprite.sl);
	printf("MAP : %dx%d\n", s->map.x, s->map.y);
	printf("POS : [%.f,%.f]\n", s->pos.x, s->pos.y);
	printf("DIR : %.f, %.f\n", s->dir.x, s->dir.y);
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
	return(1);
}
