/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omito <omito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 16:57:18 by omito             #+#    #+#             */
/*   Updated: 2026/09/05 13:59:52 by omito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buf;
	int			byte_num;
	char		*sub_buf;
	int			count_until_newline;
	static char	*stash = NULL;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free_all(&stash, buf, NULL));
	while (cheak_newline(stash, '\n', &count_until_newline) == 0)
	{
		byte_num = read(fd, buf, BUFFER_SIZE);
		if (byte_num <= 0)
			break ;
		buf[byte_num] = '\0';
		if ((strjoin(&stash, buf)) == 1)
			return (free_all(&stash, buf, NULL));
	}
	if (stash == NULL || stash[0] == '\0')
		return (free_all(&stash, buf, NULL));
	sub_buf = strcut(stash, count_until_newline);
	if (!sub_buf || store_stash_rest (&stash, count_until_newline) == 1)
		return (free_all(&stash, buf, sub_buf));
	free(buf);
	return (sub_buf);
}
