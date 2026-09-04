/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omito <omito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 16:57:18 by omito             #+#    #+#             */
/*   Updated: 2026/09/05 01:44:15 by omito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>

int	strlen(char *stash)
{
	while (*stash != NULL && (*stash)[stash_length] != '\0')
		stash_length++;
	return (stash_length);

}
int	store_stash_rest(char **stash, int count_until_newline)
{
	int		stash_length;
	char	*tmp;
	int		i;

	stash_length = 0;
	i = 0;
	while (*stash != NULL && (*stash)[stash_length] != '\0')
		stash_length++;
	tmp = malloc(sizeof(char) * (stash_length - count_until_newline + 1));
	if (!tmp)
		return (1);
	while (*stash != NULL && (*stash)[count_until_newline] != '\0')
	{
		tmp[i] = (*stash)[count_until_newline];
		i++;
		count_until_newline++;
	}
	tmp[i] = '\0';
	free(*stash);
	(*stash) = tmp;
	return (0);
}

char	*strcut(char *stash, int count_until_newline)
{
	char	*tmp;
	char	*sub_buf;

	sub_buf = malloc(sizeof(char) * (count_until_newline + 1));
	if (!sub_buf)
		return (NULL);
	tmp = sub_buf;
	while (count_until_newline--)
	{
		*sub_buf = *stash;
		sub_buf++;
		stash++;
	}
	*sub_buf = '\0';
	sub_buf = tmp;
	return (sub_buf);
}

int	strjoin(char **stash, char *buf)
{
	char	*tmp;
	int		stash_length;
	int		buf_length;
	int		total_length;

	stash_length = 0;
	buf_length = 0;
	while (*stash != NULL && (*stash)[stash_length] != '\0')
		stash_length++;
	while (buf[buf_length] != '\0')
		buf_length++;
	total_length = stash_length + buf_length + 1;
	tmp = malloc(sizeof(char) * total_length);
	if (!tmp)
		return (1);
	tmp[total_length - 1] = '\0';
	total_length--;
	while (buf_length > 0)
	{
		tmp[total_length - 1] = buf[buf_length - 1];
		total_length--;
		buf_length--;
	}
	while (stash_length > 0)
	{
		tmp[total_length - 1] = (*stash)[stash_length - 1];
		total_length--;
		stash_length--;
	}
	free(*stash);
	*stash = tmp;
	return (0);
}

int	cheak_newline(char *stash, char c, int *count_until_newline)
{
	*count_until_newline = 0;
	while (stash != NULL && *stash != '\0')
	{
		if (*stash == c)
		{
			*count_until_newline += 1;
			return (1);
		}
		stash++;
		(*count_until_newline)++;
	}
	return (0);
}

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
	if (stash == NULL || stash[0] == '\0' || byte_num = -1)
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

int	main(void)
{
	int		fd;
	char	*sub_buf;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("open_error\n");
		return (1);
	}
	while ((sub_buf = get_next_line(fd)) != NULL)
	{
		printf("%s", sub_buf);
		free(sub_buf);
	}
	close(fd);
}
//get_next_line … 上の3段階を呼ぶだけの司令塔

//utils … ft_strlen / ft_strchr / ft_strjoin 相当
//
//とりあえずBUFFER_SIZEでread
//取ってきたbufの中で改行があるか探す
//改行までを配列に格納。残りをstatic変数で保存
//またreadを繰り返して、残り＋改行
