/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omito <omito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 14:12:41 by omito             #+#    #+#             */
/*   Updated: 2026/09/05 17:44:28 by omito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*cut_and_store(char **stash, int count_until_newline, char *buf)
{
	char	*sub_buf;

	sub_buf = strcut(*stash, count_until_newline);
	if (!sub_buf || store_stash_rest (stash, count_until_newline) == 1)
		return (free_all(stash, buf, sub_buf));
	free(buf);
	return (sub_buf);
}

char	*get_next_line(int fd)
{
	char		*buf;
	int			byte_num;
	int			count_until_newline;
	static char	*stash[FD_MAX];

	if (fd >= FD_MAX || fd < 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free_all(&stash[fd], buf, NULL));
	while (cheak_newline(stash[fd], '\n', &count_until_newline) == 0)
	{
		byte_num = read(fd, buf, BUFFER_SIZE);
		if (byte_num == 0)
			break ;
		if (byte_num == -1)
			return (free_all(&stash[fd], buf, NULL));
		buf[byte_num] = '\0';
		if ((strjoin(&stash[fd], buf)) == 1)
			return (free_all(&stash[fd], buf, NULL));
	}
	if (stash[fd] == NULL || stash[fd][0] == '\0')
		return (free_all(&stash[fd], buf, NULL));
	return (cut_and_store(&stash[fd], count_until_newline, buf));
}

#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd1;
	int		fd2;

	char	*sub_buf;

	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY); 
	if (fd1 == -1 || fd2 == -1)
	{
		printf("open_error\n");
		return (1);
	}
		sub_buf = get_next_line(fd1);
		printf("%s", sub_buf);
		free(sub_buf);
		sub_buf = get_next_line(fd2);
		printf("%s", sub_buf);
		free(sub_buf);
		sub_buf = get_next_line(fd1);
		printf("%s", sub_buf);
		free(sub_buf);
		sub_buf = get_next_line(fd2);
		printf("%s", sub_buf);
		free(sub_buf);
	close(fd1);
	close(fd2);
}
