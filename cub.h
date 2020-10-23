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

#ifndef CUB_H
# define CUB_H

# include "./minilibx-linux/mlx.h"
# include "./libft/libft.h"

# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>

# define ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00
# define PINK 9961608

# define WIN_NAME "Cub3D"
# define BPP 4

# define SPEED 0.0005
# define ANGLE 5
# define FOV 0.6

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

typedef struct		s_img
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
	double			pos;
	double			step;
	int				x;
	int				y;
	int				width;
}					t_tex;

typedef struct		s_map
{
	char			**tab;
	int				h;
	int				x;
	int				y;
	int				sprite_nb;
}					t_map;

typedef struct		s_ray
{
	t_int_xy		pos;
	t_double_xy		dir;
	t_double_xy		sd;
	t_double_xy		dd;
}					t_ray;

typedef struct		s_sprite
{
	int				height;
	int				width;
	int				screen;
	double			dist;
	t_int_xy		start;
	t_int_xy		end;
	t_double_xy		pos;
	t_double_xy		delta;
	t_double_xy		depth;
}					t_sprite;

typedef	struct		s_wall
{
	t_int_xy		step;
	int				side;
	int				hit;
	int				height;
	int				start;
	int				end;
	double			perp_dist;
	double			x;
	double			*buf;
}					t_wall;

typedef struct		s_key
{
	int				esc;
	int				a;
	int				s;
	int				d;
	int				w;
	int				left;
	int				right;
}					t_key;

typedef struct		s_player
{
	t_double_xy		pos;
	t_double_xy		dir;
	t_double_xy		plane;
	t_key			key;
}					t_player;

typedef struct		s_parsing
{
	int				res;
	int				tex;
	int				color;
}					t_parsing;

typedef struct		s_struct
{
	void			*mlx;
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
	double			cam;
	unsigned int	color;
	char			*cub;
	int				i;
	int				x;
	int				y;
	void			*ptr[5];
}					t_struct;

void				ft_init(char *av1, int arg);
void				ft_init_before_parsing_1(t_struct *s);
void				ft_init_before_parsing_2(t_struct *s);
void				ft_init_raycasting_data(t_struct *s);

void				ft_parse(t_struct	*s);
void				ft_read_line(t_struct *s, char	*tmp);
void				ft_resolution(t_struct *s, char	*tmp);
t_color				ft_color(t_struct *s, char	*tmp);
unsigned int		*ft_load_tex(t_struct *s, char *tmp);

void				ft_get_pos(t_struct *s);
void				ft_load_map(t_struct *s, char *line);
void				ft_check_map_char(t_struct *s, int x, int y);
int					ft_check_map_borders(t_struct *s, int x, int y, char **map);
void				ft_check_map(t_struct *s);

int					is_space(char c);
void				ft_skip_space(t_struct *s, char *line);
int					ft_is_charset(char c, char *set);
int					ft_suffix(char *file_name, char *suffix);
char				**new_tab(t_struct *s, char **tab, char *str);

void				ft_print_arg(t_struct *s);
void				print_map(t_struct *s);
void				print_sprite(t_struct *s);

void				ft_wall(t_struct *s);
void				ft_ray_init(t_struct *s);
void				ft_ray_direction(t_struct *s);
void				ft_ray_hit(t_struct *s);

void				ft_wall_size(t_struct *s);
void				ft_wall_texture(t_struct *s);
void				ft_draw_walls(t_struct *s);
void				ft_pixel(t_struct *s);

void				ft_move_forward(t_struct *s, double sign);
void				ft_move_side(t_struct *s, double sign);
void				ft_rotate(t_struct *s, double sign);
void				ft_event(t_struct *s);

int					ft_switch_key_bol(t_struct *s, int key, int value);
int					ft_key_press(int key, void *s);
int					ft_key_release(int key, void *s);
int					ft_key_move(t_struct *s);
int					ft_expose(t_struct *s);

void				ft_sprite(t_struct *s);
void				ft_count_sprite(t_struct *s);
void				ft_sprite_pos(t_struct *s);
void				ft_sprite_distance(t_struct *s);
void				ft_sort_sprite(t_struct *s);

void				ft_sprite_transform(t_struct *s);
void				ft_sprite_size(t_struct *s);
void				ft_draw_sprite(t_struct *s);

int					ft_exit(t_struct *s);
void				ft_error(t_struct *s, int err);
int					ft_check_parsing(t_struct *s);

void				ft_bitmap(t_struct *s);
unsigned char		*ft_bmp_file_header(t_struct *s);
unsigned char		*ft_bmp_dib_header(t_struct *s);
unsigned char		*ft_bmp_pixel_array(t_struct *s);
void				ft_set_int_to_char(unsigned char *start, int value);

#endif
