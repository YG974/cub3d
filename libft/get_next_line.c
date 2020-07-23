/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:01:41 by ygeslin           #+#    #+#             */
/*   Updated: 2019/11/21 16:41:40 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_next_line(int fd, char **line)
{
		static char		gnl[NB_FD][BUFFER_SIZE + 1] = {{'\0'}};
		t_gnl			s;

		s.j = 0;
		if (fd < 0 || !line || BUFFER_SIZE < 1 || (s.i = read(fd, gnl[fd], 0)))
				return (-1);
		MALLCHECK((*line = (char *)malloc(sizeof(char) * 1)));
		*line[0] = END;
		if ((s.i = strchrgnl(gnl[fd], ENDL)) > -1)
		{
				MALLCHECK((*line = ft_strjoin_endl(*line, gnl[fd])));
				while (s.i + s.j < BUFFER_SIZE)
						return (ft_next_line(s.i, fd, &*gnl));
		}
		MALLCHECK((*line = ft_strjoin(*line, gnl[fd])));
		while ((s.ret = read(fd, gnl[fd], BUFFER_SIZE)) > 0)
		{
				gnl[fd][s.ret] = END;
				MALLCHECK((*line = ft_strjoin_endl(*line, gnl[fd])));
				if ((s.i = strchrgnl(gnl[fd], ENDL)) > -1)
						return (ft_next_line(s.i, fd, &*gnl));
		}
		gnl[fd][0] = '\0';
		return (0);
}

int	ft_next_line(int i, int fd, char gnl[NB_FD][BUFFER_SIZE + 1])
{
		int j;

		j = 0;
		while (i + j < BUFFER_SIZE)
		{
				gnl[fd][j] = gnl[fd][i + j + 1];
				j++;
		}
		return (1);
}

char		*ft_strjoin_endl(char *s1, const char *s2)
{
		int		len1;
		int		len2;
		int		i;
		char	*str;

		len1 = (s1 == NULL ? 0 : ft_strlen(s1));
		len2 = (strchrgnl(s2, ENDL) == -1 ? ft_strlen(s2) : strchrgnl(s2, ENDL));
		i = 0;
		if (!(str = malloc(sizeof(char) * (len1 + len2 + 1))))
				return (NULL);
		while (i < len1)
		{
				str[i] = s1[i];
				i++;
		}
		while (i < len1 + len2)
		{
				str[i] = s2[i - len1];
				i++;
		}
		str[i] = '\0';
		free(s1);
		return (str);
}

char		*ft_strjoin_gnl(char *s1, const char *s2)
{
		int		len1;
		int		len2;
		int		i;
		char	*str;

		len1 = (s1 == NULL ? 0 : ft_strlen(s1));
		len2 = ft_strlen(s2);
		i = 0;
		if (!(str = malloc(sizeof(char) * (len1 + len2 + 1))))
				return (NULL);
		while (i < len1)
		{
				str[i] = s1[i];
				i++;
		}
		while (i < len1 + len2)
		{
				str[i] = s2[i - len1];
				i++;
		}
		str[len1 + len2] = '\0';
		free(s1);
		return (str);
}

int			strchrgnl(const char *s, int c)
{
		int i;

		i = 0;
		c = (char)c;
		while (s[i])
		{
				if (s[i] == c)
						return (i);
				i++;
		}
		if (s[i] == c)
				return (i);
		return (-1);
}
