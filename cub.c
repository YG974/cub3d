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
	fd = open(s->cub, O_RDONLY);
	ret = 1;
	s->i = 0;
	while (ret == get_next_line(fd, line))		
	{
	s->i = 0;
	s->tmp = ft_split(s->buf, ' ');
	ft_read_line(s);
	s->i++;
	}
	close(fd);
}
void	ft_read_line(t_struct *s)
{		
		int i = 0;
		while (s->tmp[i])
		{
	//	printf("s->tmp%d :%s|\n", i, s->tmp[i]);
	//	printf("s->tmpc0 %c\n", s->tmp[0][0]);
	//	printf("s->tmpc1 %c\n", s->tmp[0][1]);
		if (ft_strncmp(s->tmp[0], "R", 1) == 0 && s->tmp[0] != '\0')
			ft_resolution(s);
		if (ft_strncmp(s->tmp[0], "NO", 2) == 0 && s->tmp[0] != '\0')
			read_texture(s, &s->tex.N);
		if (ft_strncmp(s->tmp[0], "SO", 2) == 0 && s->tmp[0] != '\0')
			read_texture(s, &s->tex.S);
		if (ft_strncmp(s->tmp[0], "WE", 2) == 0 && s->tmp[0] != '\0')
			read_texture(s, &s->tex.W);
		if (ft_strncmp(s->tmp[0], "EA", 2) == 0 && s->tmp[0] != '\0')
			read_texture(s, &s->tex.E);
		if (ft_strncmp(s->tmp[0], "S", 1) == 0 && s->tmp[0] != '\0')
			read_texture(s, &s->tex.sprite);
		if (ft_strncmp(s->tmp[0], "F", 1) == 0 && s->tmp[0] != '\0')
			printf("ARG -- >%s|\n", s->tmp[0]);
		if (ft_strncmp(s->tmp[0], "C", 1) == 0 && s->tmp[0] != '\0')
			printf("ARG -- >%s|\n", s->tmp[0]);
		printf("TEX:%s|\n", s->tex.N.path);
		printf("TEX:%s|\n", s->tex.S.path);
		printf("TEX:%s|\n", s->tex.E.path);
		printf("TEX:%s|\n", s->tex.W.path);
		i++;
		}
			
/*
		if (s->buf[s->i] == 'N' && s->buf[s->i + 1] == 'O' && 
			s->buf[s->i + 2] == ' ')
		if (s->buf[s->i] == 'S' && s->buf[s->i + 1] == 'O' && 
			s->buf[s->i + 2] == ' ')
			read_texture(s);
		if (s->buf[s->i] == 'W' && s->buf[s->i + 1] == 'E' && 
			s->buf[s->i + 2] == ' ')
			read_texture(s);
		if (s->buf[s->i] == 'S' && s->buf[s->i + 1] == ' ')
			read_texture(s);
		if (s->buf[s->i] == 'F' && s->buf[s->i + 1] == ' ')
			ft_resolution(s);
		if (s->buf[s->i] == 'C' && s->buf[s->i + 1] == ' ')
			ft_read_tex(s);
		else
			ft_read_map(s);
*/	
}

void	ft_resolution(t_struct *s)
{
		s->win_x = ft_atoi((const char *)s->tmp[1]);
		s->win_y = ft_atoi((const char *)s->tmp[2]);
		s->win_x = (s->win_x <= 0  ? WIDTH : s->win_x);
		s->win_x = (s->win_x > WIDTH ? WIDTH : s->win_x);
		s->win_y = (s->win_y <= 0 ? HEIGHT : s->win_y);
		s->win_y = (s->win_y > HEIGHT ? HEIGHT : s->win_y);
		printf("RESOLUTION %d %d \n", s->win_x, s->win_y);
}

void	ft_error(int i)
{
		write(1, "error\n", 6);
}

/*
int		read_number(t_struct *s)
{
		int i;

		i = 0;
		//return erreur s'il y a autre char que numb ou sign
		if (ft_isdigit(s->buf[s->i]))
				i = ft_atoi((const char *)&s->buf[s->i]);
		while (ft_isdigit(s->buf[s->i]))
				s->i++;
		return (i);
}
void		read_word(t_struct *s)
{
		int i;

		i = 0;
		//return erreur s'il y a autre char que numb ou sign
		if (ft_isdigit(s->buf[s->i]))
				i = ft_atoi((const char *)&s->buf[s->i]);
		while (ft_isdigit(s->buf[s->i]))
				s->i++;
		return;
}
int		read_floor_ceiling(t_struct *s)
{

}
*/

void	read_texture(t_struct *s, t_img *t)
{
	t->path = ft_strdup(s->tmp[1]);
	t->adr = mlx_xpm_file_to_image(s->mlx, t->path, &t->x, &t->y);
	printf("TEXTURE\n");
	printf("path :%s|\n", t->path);
	printf("adr :%s|\n", t->adr);
	printf("|x=%d | y =%d| \n", t->x, t->y);
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
		s.mlx = NULL;
		s.win = NULL;
		s.win_x = 0;
		s.win_y = 0;
		s.x = 0;
		s.y	= 0;
		ft_parse(&s);
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
