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

void	ft_load_map(t_struct *s, char *line)
{
	char	**tab;
	int		n;

	n = 0;
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
	tab[n] = line;
	n = 0;
	free(s->map.tab);
	s->map.tab = tab;
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
	ft_check_map_char(s, 0, 0);
	if (ft_check_map_borders(s, s->p.pos.x - 0.5, s->p.pos.y - 0.5, map) < 0)
		ft_error(s, 11);
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
	free(s->cub);
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
			if (ft_is_charset((char)s->map.tab[y][x], "NSEW 012") == 0)
				return (ft_error(s, 9));
			if (ft_is_charset(s->map.tab[y][x], "NSEW") == 1)
				i++;
			x++;
		}
		y++;
	}
	if (i >= 1)
		return (ft_error(s, 10));
}

int		ft_check_map_borders(t_struct *s, int x, int y, char **map)
{
	int		len;

	len = ft_strlen(map[y]);
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
