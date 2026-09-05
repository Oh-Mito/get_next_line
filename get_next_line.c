/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omito <omito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 16:57:18 by omito             #+#    #+#             */
/*   Updated: 2026/09/05 12:10:02 by omito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	int			byte_num;
	char		*sub_buf;
	int			count_until_newline;
	static char	*stash = NULL;

	while (cheak_newline(stash, '\n', &count_until_newline) == 0)
	{
		byte_num = read(fd, buf, BUFFER_SIZE);
		if (byte_num <= 0)
			break ;
		buf[byte_num] = '\0';
		if ((strjoin(&stash, buf)) == 1)
			return (NULL);
	}
	if (stash == NULL || stash[0] == '\0' || byte_num == -1)
	{
		free(stash);
		stash = (NULL);
		return (NULL);
	}
	sub_buf = strcut(stash, count_until_newline);
	if (store_stash_rest (&stash, count_until_newline) == 1)
		return (NULL);
	return (sub_buf);
}

//#include <stdio.h>
//#include <fcntl.h>
//
//int	main(void)
//{
//	int		fd;
//	char	*sub_buf;
//
//	fd = open("test.txt", O_RDONLY);
//	if (fd == -1)
//	{
//		printf("open_error\n");
//		return (1);
//	}
//	while ((sub_buf = get_next_line(fd)) != NULL)
//	{
//		printf("%s", sub_buf);
//		free(sub_buf);
//	}
//	close(fd);
//}

//とりあえずBUFFER_SIZEでread
//取ってきたbufの中で改行があるか探す
//改行までを配列に格納。残りをstatic変数で保存
//またreadを繰り返して、残り＋改行
