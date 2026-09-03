/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omito <omito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 16:57:18 by omito             #+#    #+#             */
/*   Updated: 2026/08/30 17:09:59 by omito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

int	strjoin(char *stash, char *buf)
{
	char *tmp;
	int	stash_length;
	int	buf_length;
	int	total_length;

	stash_length = 0;
	buf_length = 0;
	i = 0;
	while (stash[stash_length] != '\0')
	{
		stash_length++;
		tmp[stash_length] = stash[stash_length];
	}
	while (buf[buf_length] != '\0')
		buf_length++;
	total_length = stash_length + buf_length + 1;
	stash = malloc(sizeof(char) * total_length);
	if (!stash)
	{
		free(stash);
		return (1);
	}
	while (buf_length--)
	{
		stash[total_length] = buf[buf_length];
		total_length--;
	}
	while (stash_length--)
	{
		stash[total_length] = tmp[stash_length];
		total_length--;
	}
	return (0);
}

int	store_stash(char *stash)
{
	int	count;

	count = 0;
	while (*(*buf) != '\0')
		count++;
	stash = malloc(sizeof(char) * count + 1);

	if (!stash)
	{
		free(stash);
		return (1);
	}
	while (*(*buf) != '\0')
	{
		*(*stash) = *(*buf);
		*stash++;
		*buf++;
	}
	*stash = '\0';
	return (0);
}

int	*ft_strcut(char *stash, char c, int count)
{
	char	*tmp;

	sub_buf = malloc(sizeof(char) * count + 1);
	tmp = sub_buf;
	if (!sub_buf)
	{
		free(sub_buf);
		return (1);
	}
	while (count--)
	{
		*(*sub_buf) = *stash;
		*(sub_buf)++;
		stash++;
	}
	*(sub_buf) = tmp;
	return (0);
}

int	cheak_newline(char *stash, char c, int *count;)
{
	while (*stash != '\0')
	{
		if (*stash == c)
			return (1);
		stash++;
		count++;
	}
	return (0);
}
char	*get_next_line(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		byte_num;
	char	*sub_buf;
	int		count;
	static char	*stash;

	count = 0;
	while(cheak_newline(stash , '\n' &count) == 0)
	{

		byte_num = read(fd, buf, BUFFER_SIZE);
		if (bytenum == 0)
			break ;
		if (byte_num == -1)
		{
			write (1,"read_error", 10);
			close (fd);
			return (1);
		}
		buf[byte_num] = '\0';
		strjoin(stash, *buf);
	}
 	if ((strcut(stash, '\n', count)) == 1)
		return (1);
	if (store_stash (stash) == 1)
		return (1);
	return (sub_buf);
}

int	main(void)
{
	inf	fd;
	char	buf[BUFFER_SIZE + 1];
	int	byte_num;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		write(1, "error", 5);
		return (1);
	}
	get_next_line(fd);
	close(fd);
}
//get_next_line … 上の3段階を呼ぶだけの司令塔

//utils … ft_strlen / ft_strchr / ft_strjoin 相当
//
//とりあえずBUFFER_SIZEでread
//取ってきたbufの中で改行があるか探す
//改行までを配列に格納。残りをstatic変数で保存
//またreadを繰り返して、残り＋改行
