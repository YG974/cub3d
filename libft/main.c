/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygeslin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:12:40 by ygeslin           #+#    #+#             */
/*   Updated: 2019/11/21 14:26:26 by ygeslin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "libft.h" 

/*
   int main(int ac, char **av)
   {
   int fd;
   int i = 0;
   char *line;
   int ret;
   (void)ac;
   fd = open(av[1], O_RDONLY);
   printf("debut\n");
   while ((ret = get_next_line(fd, &line)) > 0)
   {
   if (line)
   printf("%s\n%d\n", line, ret);
   i++;
   free(line);
   }
   printf("%s\nFIN : %d\n", line, ret);
   close(fd);
   free(line);
   sleep (60);
   return (0);
   }
 */

int main()
{
		char **ptr;
		char *str;
		str = NULL;
		int fd = open("test.txt", O_RDONLY);
		ptr = &str;
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		fd = open("test2.txt", O_RDONLY);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		fd = 3;
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		printf("fd : %d ->%d%s\n", fd, get_next_line(fd, &str), str);
		return (0);
}
