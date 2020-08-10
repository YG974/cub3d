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
#include "./minilibx/mlx.h"
#include "./libft/libft.h"

#include <stdlib.h>
#include <math.h>
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

/* keys pre-setted values mapping LibX Functions  */
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
	t_img	N;
	t_img	S;
	t_img	W;
	t_img	E;
	t_img	sprite;
}				t_tex;

typedef struct s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct s_struct
{
	t_tex	tex;
	t_color	sky;
	t_color	floor;
	t_map	map;
	t_pos	pos;	
	t_pos	dir;	
	t_pos	plane;	
	void	*mlx;//mlx pointer
	void	*win;//window pointer
	int		win_x;//width size
	int		win_y;//height size
	void	*ptr;//image ptr of the full screen
	char	**tmp;//buffer to parse the map file with ft_split
	char	*buf;//buffer to parse data line by line with ft_split
	char	*cub;//map file name
	int		i;//counter
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
void	ft_img_adr(t_struct *s);

/* checking functions */
int		is_space(char c);
int		ft_suffix(char *file_name, char *suffix);
void	ft_print_arg(t_struct *s);
void	ft_check_parsing(t_struct *s);
void	print_map(t_struct *s);

/* errors functions */
int		ft_escape(t_struct *s);
int		ft_exit(t_struct *s);
void	ft_error(int i);
