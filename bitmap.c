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

void				ft_bitmap(t_struct *s)
{
	int				fd;
	int				pixel_array_size;
	unsigned char	*file_header;
	unsigned char	*dib_header;
	unsigned char	*pixel_array;

	if (!(fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)))
		ft_error(7);
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
		ft_error(1);
	i = 0;
	while (i < 14)
		file_header[i++] = (unsigned char)(0);
	file_size = BPP * s->win.x * s->win.y + 14 + 40;
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	ft_set_int_to_char(&file_header[2], file_size);
	ft_set_int_to_char(&file_header[10], (14 + 40));
	return (file_header);
}

unsigned char		*ft_bmp_dib_header(t_struct *s)
{
	unsigned char	*dib_header;
	int				i;

	if (!(dib_header = ft_calloc(sizeof(char), 40)))
		ft_error(1);
	i = 0;
	while (i < 40)
		dib_header[i++] = (unsigned char)(0);
	ft_set_int_to_char(&dib_header[0], (int)(40));
	ft_set_int_to_char(&dib_header[4], s->win.x);
	ft_set_int_to_char(&dib_header[8], s->win.y);
	dib_header[12] = (unsigned char)(1);
	dib_header[14] = (unsigned char)(32);
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
		ft_error(1);
	x = (s->win.y - 1) * s->win.x;
	while (x >= 0)
	{
		y = 0;
		while (y < s->win.x)
		{
			ft_set_int_to_char(&pixel_array[i], s->img.adr[x + y]);
			y++;
			i += 4;
		}
		x -= s->win.x;
	}
	return (pixel_array);
}

void				ft_set_int_to_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 8 * 2);
	start[3] = (unsigned char)(value >> 8 * 3);
}
