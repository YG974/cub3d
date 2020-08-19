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
#define BLACK 0x00000000
#define RED 0x00FF0000
#define BLUE 0x000000FF
#define YELLOW 0x00FFFF00
#define PINK 0x00FFC0CB

/* windows */
#define WIDTH 1280
#define HEIGHT 680
#define WIN_NAME "Cub3D"

/* moves settings */
#define SPEED 0.25
#define ANGLE 0.2

typedef struct	s_map
{
	char	**tab;
	int		x;
	int		y;
	
}				t_map;

typedef struct	s_color
{
	int		r;
	int		g;
	int		b;
}				t_color;

typedef struct	s_img
{
	char	*path;
	void	*ptr;
	unsigned int	*adr;
	int		x;
	int		y;
	int		endian;
	int		bpp;
	int		sl;
}				t_img;

typedef struct s_tex
{
	t_img	n;
	t_img	s;
	t_img	w;
	t_img	e;
	t_img	sprite;
	double	pos; /* where to start drawing texture */
	double	step; /* ratio to increase or decrease texture bloc size */
	int	x; /* x coordinate in the texture */
	int	y; /* y coordinate in the texture */
}				t_tex;

typedef struct	s_double_xy
{
	double	x;
	double	y;
}				t_double_xy;

typedef struct	s_xy
{
	int	x;
	int	y;
}				t_int_xy;

typedef struct	s_ray
{
	t_double_xy dir; /*ray direction*/ 
	t_double_xy sd; /* side_dist : dist from player to the next map square */
	t_double_xy dd; /* delta_dist : dist from the ray_pos to the next map square */
	t_int_xy    pos; /* ray position */
}       t_ray;

typedef struct	s_struct
{
	t_tex	tex;
	t_color	sky;
	t_color	floor;
	t_map	map;
	t_double_xy	pos;	// player position on the map
	t_double_xy	dir;	// direction of the player (vector)
	t_double_xy	plane;	/* camera plane, which is always perpendicular to player dir */
	double		cam;	// x camera coordinate : -1 is left, 0 is center, 1 is right
	t_ray		ray;	// rays sent to see if a wall or obstacle is hitten
	t_int_xy	step; /* variable to iterate every square of the map, step is negative if ray_dir < 0, so also tells us if the wall hit is NSEW combined with the side value */
	int		side;		// side of the map square is hitten (x: NS or y:EW)
	int		hit;		// 1 if the ray hits a wall or sprite 0 if empty map square

	int		col_size; /* size of the column to draw according to the distance */
	int		start; /* y coordinate to start drawing the column */
	int		end; /* y coordinate to end drawing the column */
	unsigned int	color; /* pixel color to draw */
	double	wall_x;

	void	*mlx;	//mlx pointer
	void	*win;	//window pointer

	int		win_x;	//width size
	int		win_y;	//height size
	
	void	*ptr;	//image ptr of the full screen
	unsigned int	*adr;
	
	char	**tmp;	//buffer to parse the map file with ft_split
	char	*buf;	//buffer to parse data, line by line with ft_split
	char	*cub;	//map file name
	
	int		i;		//counter
	int		x;		//x coordinate of the screen 0 is top left
	int		y;		//y coordinate of the screen 0 is top left
}				t_struct;

/* keyboard management functions */
int		key_press(int key, t_struct *s);

/* initialization functions */
void	ft_init_struct(char	*av);
void	ft_init_tex(t_struct *s);
void	ft_init_color(t_struct *s);
void	ft_init_map(t_struct *s);
void	ft_init_mlx(t_struct *s);
void	ft_init_pos(t_struct *s);

/* parsing and reading functions*/
void	ft_parse(t_struct	*s);
void	ft_read_line(t_struct *s);
int		read_number(t_struct *s);
void	skip_space(t_struct *s);
void	ft_resolution(t_struct *s);
t_color		ft_color(t_struct *s);
void	ft_map(t_struct *s);
char	**new_tab(char **tab, char *str);
void	ft_load_tex(t_struct *s);
void	ft_get_pos(t_struct *s);

/* displaying functions */
void	ft_draw_wall(t_struct *s);
void	ft_ray_init(t_struct *s);
void	ft_ray_direction(t_struct *s);
void	ft_ray_hit(t_struct *s);
void	ft_coloumn_size(t_struct *s);
void	ft_column_texture(t_struct *s);
void	ft_draw_columns(t_struct *s);
void	ft_pixel(t_struct *s);

/* checking functions */
int		is_space(char c);
int		ft_suffix(char *file_name, char *suffix);
void	ft_print_arg(t_struct *s);
void	ft_check_parsing(t_struct *s);
void	print_map(t_struct *s);

/* moving functions */
void	ft_move_forward(t_struct *s, double sign);
void	ft_move_side(t_struct *s, double sign);
void	ft_rotate(t_struct *s, double sign);

/* errors functions */
int		ft_escape(t_struct *s);
int		ft_exit(t_struct *s);
void	ft_error(int i);
