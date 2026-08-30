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
char	*get_next_line(int fd)
{
	
}
//get_next_line … 上の3段階を呼ぶだけの司令塔
//「改行が出るまで read し続ける」関数
//「stash から1行を切り出す」関数
//「stash を残りで更新する」関数
//utils … ft_strlen / ft_strchr / ft_strjoin 相当
