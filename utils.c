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

int		ft_is_charset(char c, char *set)
{
	int	i = 0;

	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
	/*return (printf("biz"));*/
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

/* 16 bytes de leaks dans cette fonction... */
char	**new_tab(t_struct *s, char **tab, char *str)
{
	char	**new_tab;
	int		n;

	n = 0;
	if (tab == NULL)
		if (!(tab = ft_calloc(sizeof(char **), 1)))
			ft_error(s, 1);
	while (tab[n])
		n++;
	if (!(new_tab = ft_calloc(sizeof(char **), (n + 2))))
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
