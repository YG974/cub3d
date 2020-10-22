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
	if (s->map.sprite_nb == 0)
	{
		ft_count_sprite(s);
		if (!(s->sprite = malloc(sizeof(t_sprite) * s->map.sprite_nb)))
			ft_error(s, 1);
	}
	ft_sprite_pos(s);
	ft_sprite_distance(s);
	ft_sort_sprite(s);
	s->i = 0;
	while (s->i < s->map.sprite_nb)
	{
		ft_sprite_transform(s);
		ft_sprite_size(s);
		ft_draw_sprite(s);
		s->i++;
	}
	s->i = -1;
	return ;
}

void	ft_count_sprite(t_struct *s)
{
	s->y = 0;
	while (s->map.tab[s->y])
	{
		s->x = 0;
		while (s->map.tab[s->y][s->x])
		{
			if (s->map.tab[s->y][s->x] == '2')
				s->map.sprite_nb++;
			s->x++;
		}
		s->y++;
	}
	return ;
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
			while (s->map.tab[s->y][s->x])
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
	return ;
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
	return ;
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
			if (s->sprite[i].dist < s->sprite[j].dist)
			{
				tmp = s->sprite[i];
				s->sprite[i] = s->sprite[j];
				s->sprite[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return ;
}
