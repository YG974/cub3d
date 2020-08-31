/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 11:54:16 by ygeslin           #+#    #+#             */
/*   Updated: 2020/03/12 18:17:07 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f' 
			|| c == ' ')
		return (1);
	return (0);
}

void	ft_skip_space(t_struct *s, char *line)
{
	while (ft_is_space(line[s->i]) == 1)
		s->i++;
	return;
}

void	ft_error(t_struct *s, int err)
{
	(err == 1) ? ft_putstr_fd("Error : calloc fail\n", 2) : 0 ;
	(err == 2) ? ft_putstr_fd("Error : wrong map file extension\n", 2) : 0;
	(err == 3) ? ft_putstr_fd("Error : wrong resolution description\n", 2) : 0;
	(err == 4) ? 
		ft_putstr_fd("Error : wrong sky or ceiling description\n", 2) : 0;
	(err == 5) ? ft_putstr_fd("Error : missing element description\n", 2) : 0;
	(err == 6) ? ft_putstr_fd("Error : wrong texture description\n", 2) : 0;
	(err == 7) ? ft_putstr_fd("Error : couldn't create bmp file\n", 2) : 0;
	ft_exit(s);
}

int		ft_suffix(char *file_name, char *suffix)
{
	int	i;

	i = ft_strlen(file_name);
	if (file_name[i - 1] == suffix[3] && file_name[i - 2] == suffix[2] &&
		file_name[i - 3] == suffix[1] && file_name[i - 4] == suffix[0] && i > 4)
		return (1);
	else
		ft_putstr_fd("Error : wrong map file extension\n", 2);
	return (0);
}

