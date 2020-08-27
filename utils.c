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

int		ft_error(int error)
{
	(error == 1) ? write(2, "Error : calloc fail\n", 20) : 0;
	(error == 2) ? write(2, "Error : wrong map file extension\n", 31) : 0;
	(error == 3) ? write(2, "Error : wrong resolution description\n", 33) : 0;
	(error == 4) ? 
		write(2, "Error : wrong sky or ceiling description\n", 34) : 0;
	(error == 5) ? write(2, "Error : missing element description\n", 34) : 0;
	(error == 6) ? write(2, "Error : wrong texture description\n", 34) : 0;
	return (-1);
}

int		ft_suffix(char *file_name, char *suffix)
{
	int		i;

	i = ft_strlen(file_name);
	if (file_name[i - 1] == suffix[3] && file_name[i - 2] == suffix[2] &&
		file_name[i - 3] == suffix[1] && file_name[i - 4] == suffix[0] && i > 4)
		return (1);
	else
		return (ft_error(2));
	return (0);
}

