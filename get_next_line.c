/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omito <omito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 16:57:18 by omito             #+#    #+#             */
/*   Updated: 2026/09/05 18:19:14 by omito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*stash = NULL;

	if (fd < 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free_all(&stash, buf, NULL));
	while (check_newline(stash, '\n', &count_until_newline) == 0)
	{
		byte_num = read(fd, buf, BUFFER_SIZE);
		if (byte_num == 0)
			break ;
		if (byte_num == -1)
			return (free_all(&stash, buf, NULL));
		buf[byte_num] = '\0';
		if ((strjoin(&stash, buf)) == 1)
			return (free_all(&stash, buf, NULL));
	}
	if (stash == NULL || stash[0] == '\0')
		return (free_all(&stash, buf, NULL));
	return (cut_and_store(&stash, count_until_newline, buf));
}
