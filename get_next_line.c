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

char	*ft_strchr(const char *str, int c)
{
	if (str == NULL)
		return (NULL);
	while (*str != '\0')
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)str);
	return (NULL);
}

int	read_until_newline(int fd, char **stash)
{
	char *buf;
	ssize_t	read_buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (1);
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (1);
	while (ft_strchr(*stash, '\n' == NULL))
	{
		read_buf = read(fd, buf, BUFFER_SIZE);
		if (read_buf < 0)
		{
			free(buf);
			free(*stash);
			return (1); 
		}
	}
}

int	*ft_strcut(char **stash, char **sub_buf, char *buf, char c)
{
	int	count;

	count = 0;
	while (*(*buf) != c)
		count++;
	sub_buf = malloc(sizeof(char) * count + 1);
	if (!sub_buf)
	{
		free(sub_buf);
		return (1);
	}
	while (count--)
	{
		*(*sub_buf) = *(*buf);
		*sub_buf++;
		*buf++;
	}
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
	return (0);
}

char	*get_next_line(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		byte_num;
	char	*sub_buf;
	char	*stash;

	while(1)
	{

		byte_num = read(fd, buf, BUFFER_SIZE);
		if (fd == 1)
			break ;
		if (byte_num == -1)
		{
			write (1,"read_error", 10);
			close (fd);
			return (1);
		}
		buf[byte_num] = '\0';
 		if ((ft_strcut(stash, sub_buf, buf, '\n')) == 1)
			return (1);

	}
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
