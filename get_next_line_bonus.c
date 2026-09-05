/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omito <omito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 14:12:41 by omito             #+#    #+#             */
/*   Updated: 2026/09/05 17:59:10 by omito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*cut_and_store(char **stash, int count_until_newline, char *buf)
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
