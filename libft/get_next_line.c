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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

#define BUFFER_SIZE 8
char	*ft_strjoin_to(char *s1, char *s2, char c);
int		ft_next_line(int i, char *s);
int		strchrgnl(char *s, int c);
/*int		ft_strlen(char *str);*/

/*		LIBC READ FUNCTION */

/*		#include <unistd.h> */
/*		retze_t read(int fd, void *buf, size_t count); */
/*		returns :	-1 if failed */
/*					0 when end of file */
/*					NB of bytes read if success */

 /* GNL FUNCTION*/
 /*	returns :	1 a line was read */
			/*  0 end of file */
			/*	-1 error occured */

int	get_next_line(int fd, char **line)
{
		/*char		*s;*/
		static char	buf[BUFFER_SIZE + 1]={'\0'};
		int				ret;

		*line = NULL;
		if (fd < 0 || !line || BUFFER_SIZE < 1 || (ret = read(fd, buf, 0)))
			return (-1);
//if static buffer contains a \n
// 1- write until \n in *line 
// 2- move from \n to \0 at the beginning of the static buffer
// 3- return 1
			/*ft_strjoin_to(s, "", '\n');*/
		/*write(1, "test\n", 5);*/
		if ((ret = strchrgnl(buf, '\n')) > -1)
			return (ft_next_line(ret, buf));
// if static buffer doesn't contain \n 
// 1- read 
// 2- check if \n
// 3- do it until finding \n
		write(1, "test\n", 5);
		if (!(*line = ft_strjoin_to(buf, *line, '\n')))
		{
			write(1, "test", 4);
			return (-1);
		}
		while ((ret = read(fd, buf, BUFFER_SIZE) > 0))
		{
			buf[ret] = '\0';
			if (!(*line = ft_strjoin_to(buf, *line, '\n')))
				return (-1);
			printf("%s\n", *line);
			/*if (ret < BUFFER_SIZE)*/
				/*return (0);*/
		write(1, "test\n", 5);
			if ((ret = strchrgnl(buf, '\n')) > -1)
				return (ft_next_line(ret, buf));
		}
		return (0);
}

/*int     ft_strlen(char *s)*/
/*{*/
        /*int i;*/

        /*i = 0;*/
        /*while (s[i] != '\0')*/
                /*i++;*/
        /*return (i);*/
/*}*/

int	ft_next_line(int i, char *s)
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

/*char		*ft_strjoin_gnl(char *s1, char *s2)*/
/*{*/
		/*int		len1;*/
		/*int		len2;*/
		/*int		i;*/
		/*char	*str;*/

		/*len1 = (s1 == NULL ? 0 : ft_strlen(s1));*/
		/*len2 = ft_strlen(s2);*/
		/*i = 0;*/
		/*if (!(str = malloc(sizeof(char) * (len1 + len2 + 1))))*/
				/*return (NULL);*/
		/*while (i < len1)*/
		/*{*/
				/*str[i] = s1[i];*/
				/*i++;*/
		/*}*/
		/*while (i < len1 + len2)*/
		/*{*/
				/*str[i] = s2[i - len1];*/
				/*i++;*/
		/*}*/
		/*str[len1 + len2] = '\0';*/
		/*free(s1);*/
		/*return (str);*/
/*}*/

int			strchrgnl(char *s, int c)
{
		int i;

		i = 0;
		c = (char)c;
		/*if (s == NULL)*/
			/*return (-1);*/
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

		c = 0;
		len1 = (s1 == NULL ? 0 : strchrgnl(s1, '\n'));
		len2 = (s2 == NULL ? 0 : strchrgnl(s2, '\n'));
		len1 = (len1 == -1 ? strchrgnl(s1, '\0') : len1);
		len2 = (len2 == -1 ? strchrgnl(s2, '\0') : len2);
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
		/*free(s1);*/
		return (str);
}
