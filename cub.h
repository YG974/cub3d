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
** keys **
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

/* keys pre-setted values mapping LibX Functions  */
#define KEY_PRESS 2
#define KEY_RELEASE 3
#define KEY_PRESS_MASK (1L<<0)
#define KEY_RELEASE_MASK (1L<<1)

/* colors */
#define WHITE 0x00FFFFFF
#define BLACK 0xFF000000
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
	//t_parsing		parse;
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
void				ft_init_file_data(t_struct *s);
void				ft_init_player(t_struct *s);
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
