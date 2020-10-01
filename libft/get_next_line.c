/**************************************************************************** */
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

#define BUFFER_SIZE 80
char	*ft_strjoin_to(char *s1, char *s2, char c);
int		ft_next_line(int i, char *s);
int			strchrgnl(const char *s, int c);

/*		LIBC READ FUNCTION */

/*		#include <unistd.h> */
/*		ssize_t read(int fd, void *buf, size_t count); */
/*		returns :	-1 if failed */
/*					0 when end of file */
/*					NB of bytes read if success */

 /* GNL FUNCTION*/
 /*	returns :	1 a line was read */
			/*  0 end of file */
			/*	-1 error occured */

int	get_next_line(int fd, char **line)
{
		static char		*s;
		char			buf[BUFFER_SIZE + 1];
		char			*tmp;
		int				ret;

		if (fd < 0 || !line || BUFFER_SIZE < 1 || (ret = read(fd, buf, 0)))
			return (-1);
//if static buffer contains a \n
// 1- write until \n in *line 
// 2- move from \n to \0 at the beginning of the static buffer
// 3- return 1
		if ((strchrgnl(s, '\n')) > -1)
			return (ft_next_line(ret, &s));
		

				)
		if (!(*line = ft_strjoin_to(s, buf, '\n')))
			return (-1);
		while ((ret = read(fd, buf, BUFFER_SIZE) > 0)
		{
			buf[ret] = '\0';
		}
				MALLCHECK((*line = ft_strjoin_endl(*line, gnl[fd])));
				while (s.i + s.j < BUFFER_SIZE)
						return (ft_next_line(s.i, fd, &*gnl));
		}
		MALLCHECK((*line = ft_strjoin(*line, gnl[fd])));
		while ((s.ret = read(fd, gnl[fd], BUFFER_SIZE)) > 0)
		{
				gnl[fd][s.ret] = '\0';
				MALLCHECK((*line = ft_strjoin_endl(*line, gnl[fd])));
				if ((s.i = strchrgnl(gnl[fd], '\n')) > -1)
						return (ft_next_line(s.i, fd, &*gnl));
		}
		return (0);
}

int	ft_next_line(int i, static char *s)
{
		int j;

		j = 0;
		while (i + j < BUFFER_SIZE)
		{
			s[j] = s[i + j + 1];
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
		len2 = (strchrgnl(s2, '\n') == -1 ? ft_strlen(s2) : strchrgnl(s2, '\n'));
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

char		*ft_strjoin_to(char *s1, char *s2, char c)
{
		int		len1;
		int		len2;
		int		i;
		char	*str;

		len1 = (s1 == NULL ? 0 : strchrgnl(s1, c));
		len2 = (s2 == NULL ? 0 : strchrgnl(s2, c));
		len1 = (len1 == -1 ? ft_strlen(s1) : len1);
		len2 = (len2 == -1 ? ft_strlen(s2) : len2);
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
