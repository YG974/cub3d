/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:07 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_check_parsing(t_struct *s)
{
	if ((s->win.x == 0 || s->win.y == 0 || s->tex.n == 0 || s->tex.s == 0 || 
				s->tex.w == 0 || s->tex.e == 0 || s->tex.sprite == 0 ||
				s->floor.r == -1 || s->floor.g == -1 || s->floor.b == -1 ||
				s->sky.r == -1 || s->sky.g == -1 || s->sky.b == -1))
		return (-1);
	else
		return (1);
}

