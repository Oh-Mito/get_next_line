/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omito <omito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 16:57:18 by omito             #+#    #+#             */
/*   Updated: 2026/09/04 23:47:11 by omito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

int	store_stash_rest(char **stash, int count_until_newline)
{
	int	stash_length;
	char *tmp;
	int	i;

	stash_length = 0;
	i = 0;
	while (*(*stash) != '\0')
	{
		stash_length++;
		(*stash)++;
	}	
	tmp = malloc(sizeof(char) * stash_length - count_until_newline + 1);
	if (!tmp)
		return (1);
	while (*tmp != '\0')
	{
		tmp[i] = (*stash)[count_until_newline];
		i++;
		count_until_newline++;
	}
	*tmp = '\0';
	free(*stash);
	(*stash) = tmp;
	free(tmp);
	return (0);
}

char	*strcut(char *stash, int count_until_newline)
{
	char	*tmp;
	char	*sub_buf;

	sub_buf = malloc(sizeof(char) * count_until_newline + 1);
	tmp = sub_buf;
	if (!sub_buf)
	{
		free(sub_buf);
		return NULL;
	}
	while (count_until_newline--)
	{
		*sub_buf = *stash;
		sub_buf++;
		stash++;
	}
	sub_buf = tmp;
	return (sub_buf);
}

int	strjoin(char **stash, char *buf)
{
	char *tmp;
	int	stash_length;
	int	buf_length;
	int	total_length;
	int	i;

	stash_length = 0;
	buf_length = 0;
	while (*stash != NULL && (*stash)[stash_length] != '\0')
		stash_length++;
	if (stash_length > 0)
	{
		tmp = malloc(sizeof(char) * stash_length);
		if (!tmp)
		{
			free(tmp);
			return (1);
		}
		while (i < stash_length)
		{
			tmp[i] = (*stash)[i];
			i++;
		}
	}
	while (buf[buf_length] != '\0')
		buf_length++;
	total_length = stash_length + buf_length + 1;
	*stash = malloc(sizeof(char) * total_length);
	if (!(*stash))
	{
		free(*stash);
		return (1);
	}
	while (stash != NULL && buf_length--)
	{
		(*stash)[total_length - 1] = buf[buf_length];
		total_length--;
	}
	while (stash_length--)
	{
		(*stash)[total_length - 1] = tmp[stash_length];
		total_length--;
	}
	free(tmp);
	return (0);
}

int	cheak_newline(char *stash, char c, int *count_until_newline)
{
	*count_until_newline = 0;
	while (stash != NULL && *stash != '\0')
	{
		if (*stash == c)
			return (1);
		stash++;
		(*count_until_newline)++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		byte_num;
	char	*sub_buf;
	int		count_until_newline;
	static char	*stash = NULL;

	count_until_newline = 0;
	while(cheak_newline(stash , '\n', &count_until_newline) == 0)
	{

		byte_num = read(fd, buf, BUFFER_SIZE);
		if (byte_num == 0)
			break ;
		if (byte_num == -1)
		{
			write (1,"read_error", 10);
			return NULL;
		}
		buf[byte_num] = '\0';
		if ((strjoin(&stash, buf)) == 1)
			return NULL;
	}
 	sub_buf = strcut(stash, count_until_newline);
	if (store_stash_rest (&stash, count_until_newline) == 1)
		return NULL;
	return (sub_buf);
}

int	main(void)
{
	int		fd;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		write(1, "error", 5);
		return (1);
	}
	free(get_next_line(fd));
	close(fd);
}
//get_next_line … 上の3段階を呼ぶだけの司令塔

//utils … ft_strlen / ft_strchr / ft_strjoin 相当
//
//とりあえずBUFFER_SIZEでread
//取ってきたbufの中で改行があるか探す
//改行までを配列に格納。残りをstatic変数で保存
//またreadを繰り返して、残り＋改行
