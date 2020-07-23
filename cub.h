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

/* liraries */
#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

/* keys */
# define ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEY_PRESS_MASK (1L<<0)
# define KEY_RELEASE_MASK (1L<<1)

/* colors */
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00

/* windows */
# define WIDTH 1280 
# define HEIGHT 680 
# define WIN_NAME "Cub3D" 

typedef struct s_map
{
	char	**tab;
	int		x;
	int		y;
}				t_map;

typedef struct s_color
{
	int		R;
	int		G;
	int		B;
}				t_color;

typedef struct s_img
{
	char	*path;
	void	*adr;
	int		x;
	int		y;
	int		endian;
	int		bpp;
	int		sl;
}				t_img;

typedef struct s_tex
{
	t_img	N;
	t_img	S;
	t_img	E;
	t_img	W;
	t_img	sprite;
}				t_tex;

typedef struct s_struct
{
	t_tex	tex;
	t_color	sky;
	t_color	floor;
	t_map	map;
	char	*cub;
	char	*buf;
	void	*mlx;
	void	*win;
	int		win_x;
	int		win_y;
	int		x;
	int		y;
	int		i;
}				t_struct;


int		ft_suffix(char *file_name, char *suffix);
int		key_press(int key, t_struct *s);
void	ft_init_mlx(t_struct *s);
void	ft_init_struct(char	*av);
int		ft_escape(t_struct *s);
int		ft_exit(t_struct *s);
int		ft_suffix(char *file_name, char *suffix);
void	ft_parse(t_struct	*s);
void	ft_img_adr(t_struct *s);
void	ft_init_tex(t_struct *s);
void	ft_init_color(t_struct *s);
void	ft_init_map(t_struct *s);
void	ft_read_line(t_struct *s);
void	ft_resolution(t_struct *s);
void	ft_error(int i);
int		is_space(char c);
