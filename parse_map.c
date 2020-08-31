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

/* if c == 0, skip because GNL return NULL if the line is empty */
void	ft_load_map(t_struct *s, char *line)
{
	char	*tmp;
	char	c;
	
	c = line[0];
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f' || c == 0)
		return (free(tmp));
	tmp = ft_strdup(line);
	s->map.tab = new_tab(s->map.tab, tmp);
}

void	ft_check_map_NSEW(t_struct *s)
{
	int		i;

	i = 0;
	s->map.y = 0;
	while (s->map.tab[s->map.y])
	{
		s->map.x = 0;
		while (s->map.tab[s->map.y][s->map.x])
		{
			if (s->map.tab[s->map.y][s->map.x] != 'N' &&
				s->map.tab[s->map.y][s->map.x] != 'S' &&
				s->map.tab[s->map.y][s->map.x] != 'E' &&
				s->map.tab[s->map.y][s->map.x] != 'W' &&
				s->map.tab[s->map.y][s->map.x] != '2' &&
				s->map.tab[s->map.y][s->map.x] != ' ' &&
				s->map.tab[s->map.y][s->map.x] != '1' &&
				s->map.tab[s->map.y][s->map.x] != '0' )
				return (ft_error(s, 9));
			s->map.x++;
		}
		s->map.y++;
	}
}

void	ft_check_map_char(t_struct *s)
{
	int		i;

	i = 0;
	s->map.y = 0;
	while (s->map.tab[s->map.y])
	{
		s->map.x = 0;
		while (s->map.tab[s->map.y][s->map.x])
		{
			if (s->map.tab[s->map.y][s->map.x] != 'N' &&
				s->map.tab[s->map.y][s->map.x] != 'S' &&
				s->map.tab[s->map.y][s->map.x] != 'E' &&
				s->map.tab[s->map.y][s->map.x] != 'W' &&
				s->map.tab[s->map.y][s->map.x] != '2' &&
				s->map.tab[s->map.y][s->map.x] != ' ' &&
				s->map.tab[s->map.y][s->map.x] != '1' &&
				s->map.tab[s->map.y][s->map.x] != '0' )
				return (ft_error(s, 9));
			s->map.x++;
		}
		s->map.y++;
	}
}

void	ft_check_map_borders(t_struct *s)
{
	s->map.y = 0;
	while (s->map.tab[s->map.y])
	{
		s->map.x = 0;
		while (s->map.tab[s->map.y][s->map.x])
		{
			if (s->map.tab[s->map.y][s->map.x] != 'N' &&
				s->map.tab[s->map.y][s->map.x] != 'S' &&
				s->map.tab[s->map.y][s->map.x] != 'E' &&
				s->map.tab[s->map.y][s->map.x] != 'W' &&
				s->map.tab[s->map.y][s->map.x] != '2' &&
				s->map.tab[s->map.y][s->map.x] != ' ' &&
				s->map.tab[s->map.y][s->map.x] != '1' &&
				s->map.tab[s->map.y][s->map.x] != '0' )
				return (ft_error(s, 9));
			s->map.x++;
		}
		s->map.y++;
	}
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

char	**new_tab(char **tab, char *str)
{
	char	**new_tab;
	int		n;

	n = 0;
	while (tab[n])
		n++;
	if (!(new_tab = malloc(sizeof(char **) * (n + 2))))
	{
		write(2, "Error : calloc fail\n", 20);
		return (NULL);
	}
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

