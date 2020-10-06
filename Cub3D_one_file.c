/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:07 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/* https://en.wikipedia.org/wiki/BMP_file_format */
void				ft_bitmap(t_struct *s)
{
	int				fd;
	int				pixel_array_size;
	unsigned char	*file_header;
	unsigned char	*dib_header;
	unsigned char	*pixel_array;

	if (!(fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)))
		ft_error(s, 7);
	ft_wall(s);
	pixel_array_size = BPP * s->win.x * s->win.y;
	file_header = ft_bmp_file_header(s);
	dib_header = ft_bmp_dib_header(s);
	pixel_array = ft_bmp_pixel_array(s);
	write(fd, file_header, 14);
	write(fd, dib_header, 40);
	write(fd, pixel_array, pixel_array_size);
	free(file_header);
	free(dib_header);
	free(pixel_array);
	close(fd);
	exit(0);
}

unsigned char		*ft_bmp_file_header(t_struct *s)
{
	unsigned char	*file_header;
	int				i;
	int				file_size;

	if (!(file_header = ft_calloc(sizeof(char), 14)))
		ft_error(s, 1);
	i = 0;
	while (i < 14)
		file_header[i++] = (unsigned char)(0);
	file_size = BPP * s->win.x * s->win.y + 14 + 40;
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	ft_set_int_to_char(&file_header[2], file_size);/* file size */
	ft_set_int_to_char(&file_header[10], (14 + 40));/* adr img array start */
	return (file_header);
}

 unsigned char		*ft_bmp_dib_header(t_struct *s)
{
	unsigned char	*dib_header;
	int				i;

	if (!(dib_header = ft_calloc(sizeof(char), 40)))
		ft_error(s, 1);
	i = 0;
	while (i < 40)
		dib_header[i++] = (unsigned char)(0);
	ft_set_int_to_char(&dib_header[0], (int)(40));	/* DIB header size */
	ft_set_int_to_char(&dib_header[4], s->win.x);	/* width in pixels */
	ft_set_int_to_char(&dib_header[8], s->win.y);	/* height in pixels */
	dib_header[12] = (unsigned char)(1);			/* nb of color planes */
	dib_header[14] = (unsigned char)(32);			/* bit per pixel */
	return (dib_header);
}

unsigned char		*ft_bmp_pixel_array(t_struct *s)
{
	unsigned char	*pixel_array;
	int				i;
	int				x;
	int				y;

	i = 0;
	if (!(pixel_array = ft_calloc(sizeof(unsigned char),
					s->win.x * s->win.y * BPP)))
		ft_error(s, 1);
	x = (s->win.y - 1) * s->win.x;
	while (x >= 0)
	{
		y = 0;
		while (y < s->win.x)
		{
			ft_set_int_to_char(&pixel_array[i], s->img.adr[x + y]);
			y++;
			i += 4; /*inc by 4 because convert 1 int into 4 chars */
		}
		x -= s->win.x;
	}
	return (pixel_array);
}

void			ft_set_int_to_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 8 * 2);
	start[3] = (unsigned char)(value >> 8 * 3);
}
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

void	ft_init(char *av1, int arg)
{
	t_struct	s;
	int			tab[3];

	s.cub = ft_strdup(av1);
	s.mlx = mlx_init();
	ft_init_before_parsing_1(&s);
	ft_init_before_parsing_2(&s);
	ft_parse(&s);
	ft_init_raycasting_data(&s);
	s.img.ptr = mlx_new_image(s.mlx, s.win.x, s.win.y);
	s.img.adr = (unsigned int*)mlx_get_data_addr(s.img.ptr, 
			&tab[0], &tab[1],&tab[2]);
	if (arg == 1)
		ft_bitmap(&s);
	s.win.ptr = mlx_new_window(s.mlx, s.win.x, s.win.y, WIN_NAME);
	/*ft_print_arg(&s);*/
	/*print_map(&s);*/
	/*mlx_put_image_to_window(s.mlx, s.win.ptr, s.img.ptr, 0, 0);*/
	ft_wall(&s);
	mlx_put_image_to_window(s.mlx, s.win.ptr, s.img.ptr, 0, 0);
	mlx_hook(s.win.ptr, KEY_PRESS, KEY_PRESS_MASK, key_press, &s);
	/*mlx_hook(s.win.ptr, KEY_RELEASE, KEY_RELEASE_MASK, key_press, &s);*/
	mlx_loop(s.mlx);
	exit(0);
	return;
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
}

void	ft_init_before_parsing_2(t_struct *s)
{
	s->map.x = 0;
	s->map.y = 0;
	s->map.sprite_nb = 0;
	s->map.tab = 0;
	s->cam = 0.0;
	s->p.pos.x = 0.0;
	s->p.pos.y = 0.0;
	s->p.dir.x = 0.0;
	s->p.dir.y = 0.0;
	s->p.plane.x = 0.0;
	s->p.plane.y = 0.0;
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
	ft_wall(s);
	mlx_put_image_to_window(s->mlx, s->win.ptr, s->img.ptr, 0, 0);
	/*free(s->win.ptr);*/
	/*free(s->img.ptr);*/
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
	/*printf("x: %d | y: %d | c: %c\n", x, y, s->map.tab[y][x]);*/
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
	s->p.dir.x = s->p.dir.x  * cos(rot) - s->p.dir.y * sin(rot);
	s->p.dir.y = old_dir_x * sin(rot) + s->p.dir.y * cos(rot);
	s->p.plane.x = s->p.plane.x * cos(rot) - s->p.plane.y  * sin(rot);
	s->p.plane.y = old_plane_x * sin(rot) + s->p.plane.y  * cos(rot);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:07 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/* read map file, parse until the end, check errors */
void			ft_parse(t_struct *s)
{
	char		*line;
	int			fd;
	int			ret;

	line = NULL;
	if (!(fd = open(s->cub, O_RDONLY)))
		ft_error(s, 8);
	ret = 1;
	s->x = 0;
	while (ret == get_next_line(fd, &line))
	{
		s->i = 0;
		if (ft_check_parsing(s) == 1)
			ft_load_map(s, line);
		else
		{
			ft_read_line(s, line);
			free(line);
		}
		/*printf("%s\n", line);*/
	}
	free(line);
	if (ft_check_parsing(s) == -1)
		ft_error(s, 5);
	ft_get_pos(s);
	ft_check_map(s);
	ft_print_arg(s);
	if (s->parse.tex != 5 || s->parse.color != 2 || s->parse.res != 1)
		ft_error(s, 13);
	close(fd);
}

/* read line to know which map description it is */
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

/* parse input line and store mlx window size resolution */
void			ft_resolution(t_struct *s, char *line)
{
	char			**tab;
	int				i;

	i = 0;
	s->i++;
	tab = ft_split(&line[s->i], ' ');
	while (tab[i])
		i++;
	if (i != 2)
		ft_error(s, 3);
	s->win.x = ft_atoi((const char *)tab[0]);
	s->win.y = ft_atoi((const char *)tab[1]);
	s->win.x = (s->win.x <= 0 ? WIDTH : s->win.x);
	s->win.x = (s->win.x > WIDTH ? WIDTH : s->win.x);
	s->win.y = (s->win.y <= 0 ? HEIGHT : s->win.y);
	s->win.y = (s->win.y > HEIGHT ? HEIGHT : s->win.y);
	while (i >= 0)
		free(tab[i--]);
	s->parse.res++;
	free(tab);
}

/* parse input line and return struct with RGB color */
t_color			ft_color(t_struct *s, char *line)
{
	t_color			color;
	char			**tab;
	int				i;

	i = 0;
	s->i += 1;
	tab = ft_split(&line[s->i], ',');
	while (tab[i])
		i++;
	if (i != 3)
		ft_error(s, 4);
	color.r = ft_atoi((const char *)tab[0]);
	color.g = ft_atoi((const char *)tab[1]);
	color.b = ft_atoi((const char *)tab[2]);
	if (color.r > 255 || color.r < 0 || color.g > 255 || color.g < 0 ||
			color.b > 255 || color.b < 0)
		ft_error(s, 4);
	while (i >= 0)
		free(tab[i--]);
	free(tab);
	s->parse.color++;
	return (color);
}

/* return ptr to tex img imported in mlx(cast in unsigned int to modify it) */
unsigned int	*ft_load_tex(t_struct *s, char *line)
{
	void			*ptr;
	int				tmp[5];
	unsigned int	*adr;
	char			**tab;
	int				i;

	i = 0;
	s->i += 2;
	tab = ft_split(&line[s->i], ' ');
	while (tab[i])
		i++;
	if (i != 1)
		ft_error(s, 6);
	ptr = mlx_xpm_file_to_image(s->mlx, tab[0], &tmp[0], &tmp[1]);
	if (tmp[0] != tmp[1])
		ft_error(s, 12);
	s->tex.width = tmp[0];
	adr = (unsigned int*)mlx_get_data_addr(ptr, &tmp[2], &tmp[3], &tmp[4]);
	free(ptr);
	free(tab[0]);
	free(tab);
	s->parse.tex++;
	return (adr);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:07 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_add_line(t_struct *s, char *str)
{
	char	**tab;
	int		n;

	n = 0;
	if (s->map.tab == NULL)
	{
		if (!(s->map.tab = ft_calloc(sizeof(char *), 2)))
			ft_error(s, 1);
		s->map.tab[0] = str;
		free(s->map.tab[1]);
	}
	else
	{
		while (s->map.tab[n])
			n++;
		if (!(tab = ft_calloc(sizeof(char *), n + 2)))
			ft_error(s, 1);
		n = 0;
		while (s->map.tab[n])
		{
			tab[n] = s->map.tab[n];
			n++;
		}
		tab[n] = str;
		n = 0;
		/*while (s->map.tab[n])*/
			/*free(s->map.tab[n++]);*/
		free(s->map.tab);
		s->map.tab = tab;
	}
}
void	ft_load_map(t_struct *s, char *line)
{
	/*char	*tmp;*/

	/*tmp = ft_strdup(line);*/
	/*if (tmp [0] == '\0')*/
	/*{*/
		/*free(tmp);*/
		/*return ;*/
	/*}*/
	/*else*/
		ft_add_line(s, line);
	/*while(1);*/
	/*printf("%p\n", s->map.tab);*/
	/*if (!s->map.tab)*/
		/*if (!(s->map.tab = ft_calloc(sizeof(char **), 1)))*/
			/*ft_error(s, 1);*/
	/*if (line[0] != '\0' || line[0] == '\n')*/
	/*{*/
	/*tmp = ft_strdup(line);*/
	/*s->map.tab = new_tab(s, s->map.tab, tmp);*/
	/*printf("%p\n", s->map.tab);*/
	/*}*/
	/*else*/
		/*free(tmp);*/
	/*printf("%s\n", tmp);*/
	/*x = ft_strdup("x");*/
	/*t = 0;*/
	/*s->x++;*/
	/*if (s->x == 20)*/
		/*while(1);*/
	return ;
}

void	ft_check_map(t_struct *s)
{
	char	**map;
	char	*tmp;
	int		i;

	i = 0;
	if (!(map = ft_calloc(sizeof(char **), 1)))
		ft_error(s, 1);
	while (s->map.tab[i])
	{
		tmp = ft_strdup(s->map.tab[i++]);
		map = new_tab(s, map, tmp);
	}
	s->map.h = i;
	printf("height%d\n", i);
	ft_check_map_char(s, 0, 0);
	if (ft_check_map_borders(s, s->p.pos.x - 0.5, s->p.pos.y - 0.5, map) < 0)
		ft_error(s, 11);
	i = 0;
	while (map[i])
		free(map[i++]);
	/*{*/
		/*printf("%s\n", map[i++]);*/
	/*}*/
	free(map);
// free tous les tab
}

void	ft_check_map_char(t_struct *s, int x, int y)
{
	int		i;

	i = 0;
	while (s->map.tab[y])
	{
		x = 0;
		while (s->map.tab[y][x])
		{
			/*if (s->map.tab[y][x] == '\n' || s->map.tab[y][x] == '\0')*/
				/*x = x;*/
			if (ft_is_charset((char)s->map.tab[y][x], "NSEW 012") == 0)
				return (ft_error(s, 9));
			if (ft_is_charset(s->map.tab[y][x], "NSEW") == 1)
				i++;
			x++;
		}
		y++;
	}
	if (i > 1)
		return (ft_error(s, 10));
}

int		ft_check_map_borders(t_struct *s, int x, int y, char **map)
{
	int		len;

	len = ft_strlen(map[y]) ;
	if (x >= len)
		return (-1);
	if (x == -1 || y == -1 || y == s->map.h)
		return (-1);
	if (x > len)
		return (-1);
	if (map[y][x] == '1' || map[y][x] == '9')
		return (1);
	map[y][x] = '9';
	if (ft_check_map_borders(s, x, y - 1, map) < 0)
		return (-1);
	if (ft_check_map_borders(s, x + 1, y, map) < 0)
		return (-1);
	if (ft_check_map_borders(s, x, y + 1, map) < 0)
		return (-1);
	if (ft_check_map_borders(s, x - 1, y, map) < 0)
		return (-1);
	return (1);
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
			s->p.plane.x = FOV * -s->p.dir.y;
			if (s->map.tab[s->map.y][s->map.x] == 'E')
				s->p.dir.x = 1;
			if (s->map.tab[s->map.y][s->map.x] == 'W')
				s->p.dir.x = -1;
			s->p.plane.y = FOV * -s->p.dir.x;
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
#include "cub.h"

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

void	ft_print_arg(t_struct *s)
{
	printf("RESOLUTION : %d x %d\n", s->win.x, s->win.y);
	printf("FLOOR : %d,%d,%d\n", s->floor.r, s->floor.g, s->floor.b);
	printf("SKY : %d,%d,%d\n", s->sky.r, s->sky.g, s->sky.b);
	printf("MAP : %dx%d\n", s->map.x, s->map.y);
	printf("POS : [%.f,%.f]\n", s->p.pos.x, s->p.pos.y);
	printf("DIR : %.f, %.f\n", s->p.dir.x, s->p.dir.y);
	printf("texture width : %d\n", s->tex.width);
	printf("texture N : %p\n", s->tex.n);
	printf("texture s : %p\n", s->tex.s);
	printf("texture e : %p\n", s->tex.e);
	printf("texture w : %p\n", s->tex.w);
	printf("texture S : %p\n", s->tex.sprite);
	print_map(s);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:07 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_sprite(t_struct *s)
{
	if ( s->map.sprite_nb == 0)
	{
		ft_count_sprite(s);
		if (!(s->sprite = malloc(sizeof(t_sprite) * s->map.sprite_nb)))
			ft_error(s, 1);
	}
	ft_sprite_pos(s);
	ft_sprite_distance(s);
	ft_sort_sprite(s);
	s->i = 0;
	/*printf("\n");*/
	while (s->i < s->map.sprite_nb)
	{
		ft_sprite_transform(s);
		ft_sprite_size(s);
		ft_draw_sprite(s);
		/*print_sprite(s);*/
		s->i++;
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

void	ft_sprite_pos(t_struct *s)
{
	int			i;

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

void	ft_sprite_distance(t_struct *s)
{
	int			i;

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
	int			i;
	int			j;
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:07 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
	int		x;
	int		y;
	int		d;

	x = s->sprite[s->i].start.x;
	while (x < s->sprite[s->i].end.x)
	{
		s->tex.x = (int)(256 * (x - (-s->sprite[s->i].width / 2 + 
				s->sprite[s->i].screen)) * 64 / s->sprite[s->i].width) / 256;
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:07 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f' 
			|| c == ' ')
		return (1);
	return (0);
}

void	ft_skip_space(t_struct *s, char *line)
{
	while (ft_is_space(line[s->i]) == 1)
		s->i++;
	return;
}

int		ft_is_charset(char c, char *set)
{
	int	i = 0;

	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
	/*return (printf("biz"));*/
}

int		ft_suffix(char *file_name, char *suffix)
{
	int	i;

	i = ft_strlen(file_name);
	if (file_name[i - 1] == suffix[3] && file_name[i - 2] == suffix[2] &&
		file_name[i - 3] == suffix[1] && file_name[i - 4] == suffix[0] && i > 4)
		return (1);
	else
		ft_putstr_fd("Error : wrong map file extension\n", 2);
	return (0);
}

/* 16 bytes de leaks dans cette fonction... */
char	**new_tab(t_struct *s, char **tab, char *str)
{
	char	**new_tab;
	int		n;

	n = 0;
	/*if (tab == NULL)*/
		/*if (!(tab = ft_calloc(sizeof(char **), 1)))*/
			/*ft_error(s, 1);*/
	/*printf("kikoo : %s\n", str);*/
	/*printf("%p\n", tab);*/
	while (tab[n])
		n++;
	if (!(new_tab = ft_calloc(sizeof(char *), (n + 2))))
		ft_error(s, 1);
	n = 0;
	while (tab[n])
	{
		new_tab[n] = tab[n];
		n++;
	}
	/*printf("%p\n", new_tab);*/
	free(tab[n]);
	free(tab);
	new_tab[n] = str;
	new_tab[n + 1] = NULL;
	return (new_tab);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:07 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_exit(t_struct *s)
{
	int	i;

	i = 0;
	while (s->map.tab[i])
		free(s->map.tab[i++]);
	/*if (s->win.ptr)*/
	/*{*/
		/*mlx_destroy_window(s->mlx, s->win.ptr);*/
		/*free(s->win.ptr);*/
	/*}*/
	free(s->cub);
	free(s->wall.buf);
	free(s->tex.n);
	free(s->tex.s);
	free(s->tex.e);
	free(s->tex.w);
	free(s->tex.sprite);
	/*if (s->img.ptr)*/
		/*free(s->img.ptr);*/
	/*if (s->img.adr)*/
		/*free(s->img.adr);*/
	/*if (s->mlx)*/
		/*free(s->mlx);*/
	exit(0);
}

void	ft_error(t_struct *s, int err)
{
	s->x = 0;
	(err == 1) ? ft_putstr_fd("Error : calloc fail\n", 2) : 0 ;
	(err == 2) ? ft_putstr_fd("Error : wrong map file extension\n", 2) : 0;
	(err == 3) ? ft_putstr_fd("Error : wrong resolution description\n", 2) : 0;
	(err == 4) ?
		ft_putstr_fd("Error : wrong sky or ceiling description\n", 2) : 0;
	(err == 5) ? ft_putstr_fd("Error : missing element description\n", 2) : 0;
	(err == 6) ? ft_putstr_fd("Error : wrong texture description\n", 2) : 0;
	(err == 7) ? ft_putstr_fd("Error : couldn't create bmp file\n", 2) : 0;
	(err == 8) ? ft_putstr_fd("Error : couldn't open map file\n", 2) : 0;
	(err == 9) ?
		ft_putstr_fd("Error : map contains forbidden characters\n", 2) : 0;
	(err == 10) ? ft_putstr_fd("Error : multiple starting position\n", 2) : 0;
	(err == 11) ? ft_putstr_fd("Error : map is not closed\n", 2) : 0;
	(err == 12) ?
		ft_putstr_fd("Error : Error : texture image is not a square\n", 2) : 0;
	(err == 13) ?
		ft_putstr_fd("Error : duplicated element description\n", 2) : 0;
	exit(0);
	/*ft_exit(s);*/
}

int		ft_check_parsing(t_struct *s)
{
	if ((s->win.x == 0 || s->win.y == 0 || s->tex.n == 0 || s->tex.s == 0 ||
		s->tex.w == 0 || s->tex.e == 0 || s->tex.sprite == 0 ||
		s->floor.r == -1 || s->floor.g == -1 || s->floor.b == -1 ||
		s->sky.r == -1 || s->sky.g == -1 || s->sky.b == -1))
		return (-1);
	else
		return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:07 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_wall(t_struct *s)
{
	s->x = 0;
	while (s->x < s->win.x)
	{
		ft_ray_init(s);
		ft_ray_direction(s);
		ft_ray_hit(s);
		ft_wall_size(s);
		ft_wall_texture(s);
		ft_draw_walls(s);
		printf("----------------TESTEST\ns wall x %f\ns tex x %d\ns tex y %d\n-----------\n",s->wall.x, s->tex.x, s->tex.y);
		s->x++;
	}
	ft_sprite(s);
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
void	ft_wall_size(t_struct *s)
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:07 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/* remplacer les 64 par texture_width) */
void	ft_wall_texture(t_struct *s)
{
	s->tex.x = (int)(s->wall.x * s->tex.width);
	if (s->wall.side == 0 && s->ray.dir.x > 0)
		s->tex.x = s->tex.width - s->tex.x - 1;
	if (s->wall.side == 1 && s->ray.dir.y < 0)
		s->tex.x = s->tex.width - s->tex.x - 1;
	s->tex.step = (double)s->tex.width / s->wall.height;
	s->tex.pos = (s->wall.start - s->win.y / 2 + s->wall.height / 2)
		* s->tex.step;
}

void	ft_draw_walls(t_struct *s)
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
		s->y++;
	}
	s->color = s->floor.r * 256 * 256 + s->floor.g * 256 + s->floor.b;
	while (s->y < s->win.y)
			s->img.adr[s->x + s->win.x * s->y++] = s->color;
}

void	ft_pixel(t_struct *s)
{
	int	pix_nb;

	pix_nb = s->tex.width * s->tex.y + s->tex.x;
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:51:38 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:08 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//cmd to get resolution on macos
//system_profiler SPDisplaysDataType | grep Resolution
/*get resolution on ubuntu*/
/*xrandr | fgrep '*'*/

/*
** libraries **
*/
#include "./minilibx/mlx.h"
#include "./libft/libft.h"

#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

/*
*	keys mac*
*/
#define ESC 53
#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_UP 126
#define KEY_DOWN 125
#define KEY_LEFT 123
#define KEY_RIGHT 124
/*
*	keys linux*
#define ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
*/

/* keys pre-setted values mapping LibX Functions  */
#define KEY_PRESS 2
#define KEY_RELEASE 3
#define KEY_PRESS_MASK (1L<<0)
#define KEY_RELEASE_MASK (1L<<1)

/* colors */
//macos black
#define BLACK 0xFF000000
//linux black
//#define BLACK 0000000000
#define WHITE 0x00FFFFFF
#define RED 0x00FF0000
#define BLUE 0x000000FF
#define YELLOW 0x00FFFF00
//#define PINK 0x00FFC0CB
#define PINK 9961608

/* windows */
#define WIDTH 1280
#define HEIGHT 680
#define WIN_NAME "Cub3D"
#define BPP 4

/* moves settings */
#define SPEED 0.2
#define ANGLE 0.1
#define FOV 0.7

typedef struct		s_xy
{
	int				x;
	int				y;
}					t_int_xy;

typedef struct		s_double_xy
{
	double			x;
	double			y;
}					t_double_xy;

typedef struct		s_win
{
	void			*ptr;
	int				x;
	int				y;
}					t_win;

typedef struct	s_img
{
	void			*ptr;
	unsigned int	*adr;
}					t_img;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
	unsigned int	*color;
}					t_color;

typedef struct		s_tex
{
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*w;
	unsigned int	*e;
	unsigned int	*sprite;
	double			pos; /* where to start drawing texture */
	double			step; /* ratio to increase or decrease texture bloc size */
	int				x; /* x coordinate in the texture */
	int				y; /* y coordinate in the texture */
	int				width; /* texture bloc width */
}					t_tex;

typedef struct	s_map
{
	char			**tab;
	int				h;
	int				x;
	int				y;
	int				sprite_nb;
	
}					t_map;

typedef struct		s_ray
{
	t_int_xy		pos; /* ray position */
	t_double_xy		dir; /*ray direction*/ 
	t_double_xy		sd; /* side_dist : dist from player to the next map square until hitting a wall */
	t_double_xy		dd; /* delta_dist : dist from the ray_pos to the next map square */
}					t_ray;

typedef struct	s_sprite
{
	int				height;
	int				width;
	int				screen;
	double			dist;
	t_int_xy		start; /* y coordinate to start drawing the wall */
	t_int_xy		end; /* y coordinate to end drawing the wall */
	t_double_xy		pos;
	t_double_xy		delta; /* relative x and y coordinate from the player */
	t_double_xy		depth;
}					t_sprite;

typedef	struct		s_wall
{
	t_int_xy		step; /* variable to iterate every square of the map, step is negative if ray_dir < 0, so also tells us if the wall hit is NSEW combined with the side value */
	int				side; /* wich side of the wall is hitten (x or y coordinate) to know to texture to select */
	int				hit; /* hit = 1 if the wall is hitten, in order to quite the loop */
	int				height; /* height of the wall calculated from the distance */
	int				start; /* y coordinate where to start drawing the wall stripe */
	int				end; /* y coordinate where to start drawing the wall stripe */
	double			perp_dist; /* perpendicular distance of wall from the player plane */
	double			x; /*x coordinate of the hitten wall, in order to know the x coordinate of the texture to pick */
	double			*buf; /* buffer to keep wall distances in order to sorte sprite and not display sprites behind walls */
}					t_wall;

typedef struct		s_player
{
	t_double_xy		pos;	// player position on the map
	t_double_xy		dir;	// direction of the player (vector)
	t_double_xy		plane;	/* camera plane, which is always perpendicular to player dir */
}					t_player;

typedef struct		s_parsing
{
	int				res;
	int				tex;
	int				color;
}					t_parsing;

typedef struct		s_struct
{
	void			*mlx;	//mlx pointer
	t_parsing		parse;
	t_win			win;
	t_img			img;
	t_color			sky;
	t_color			floor;
	t_tex			tex;
	t_map			map;
	t_player		p;
	t_ray			ray;
	t_wall			wall;
	t_sprite		*sprite;
	double			cam;	/* x cam coordinate : -1 = left | 0 = center | 1 = right */
	unsigned int	color;	/* pixel color to draw */
	char			*cub;	//map file name
	int				i;		//counter
	int				x;		//x coordinate of the screen 0 is top left
	int				y;		//y coordinate of the screen 0 is top left
}					t_struct;


/* cub.c */
void				ft_init(char *av1, int arg);
void				ft_init_before_parsing_1(t_struct *s);
void				ft_init_before_parsing_2(t_struct *s);
void				ft_init_raycasting_data(t_struct *s);

/* parse.c */
void				ft_parse(t_struct	*s);
void				ft_read_line(t_struct *s, char	*tmp);
void				ft_resolution(t_struct *s, char	*tmp);
t_color				ft_color(t_struct *s, char	*tmp);
unsigned int		*ft_load_tex(t_struct *s, char *tmp);

/* parse_map.c */
void				ft_get_pos(t_struct *s);
void				ft_load_map(t_struct *s, char *line);
void				ft_check_map_char(t_struct *s, int x, int y);
int					ft_check_map_borders(t_struct *s, int x, int y, char **map);
void				ft_check_map(t_struct *s);

/* utils.c */
int					is_space(char c);
void				ft_skip_space(t_struct *s, char *line);
int					ft_is_charset(char c, char *set);
int					ft_suffix(char *file_name, char *suffix);
char				**new_tab(t_struct *s, char **tab, char *str);

/* print.c */
void				ft_print_arg(t_struct *s);
void				print_map(t_struct *s);
void				print_sprite(t_struct *s);

/* wall_1.c */
void				ft_wall(t_struct *s);
void				ft_ray_init(t_struct *s);
void				ft_ray_direction(t_struct *s);
void				ft_ray_hit(t_struct *s);

/* wall_2.c */
void				ft_wall_size(t_struct *s);
void				ft_wall_texture(t_struct *s);
void				ft_draw_walls(t_struct *s);
void				ft_pixel(t_struct *s);

/* move.c */
int					key_press(int key, t_struct *s);
void				ft_move_forward(t_struct *s, double sign);
void				ft_move_side(t_struct *s, double sign);
void				ft_rotate(t_struct *s, double sign);
void				ft_event(t_struct *s);

/* sprite_1.c */
void				ft_sprite(t_struct *s);
void				ft_count_sprite(t_struct *s);
void				ft_sprite_pos(t_struct *s);
void				ft_sprite_distance(t_struct *s);
void				ft_sort_sprite(t_struct *s);

/* sprite_2.c */
void				ft_sprite_transform(t_struct *s);
void				ft_sprite_size(t_struct *s);
void				ft_draw_sprite(t_struct *s);

/* utils_2.c */
int					ft_exit(t_struct *s);
void				ft_error(t_struct *s, int err);
int					ft_check_parsing(t_struct *s);

/* bitmap.c */
void			ft_bitmap(t_struct *s);
unsigned char	*ft_bmp_file_header(t_struct *s);
unsigned char	*ft_bmp_dib_header(t_struct *s);
unsigned char	*ft_bmp_pixel_array(t_struct *s);
void			ft_set_int_to_char(unsigned char *start, int value);
