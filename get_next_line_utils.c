/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omito <omito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 11:41:42 by omito             #+#    #+#             */
/*   Updated: 2026/09/05 13:59:43 by omito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_all(char **stash, char *buf, char *sub_buf)
{
	free(*stash);
	free(buf);
	free(sub_buf);
	*stash = (NULL);
	return (NULL);
}

int	store_stash_rest(char **stash, int count_until_newline)
{
	int		stash_length;
	char	*tmp;
	int		i;

	i = 0;
	stash_length = 0;
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
	int		s_len;
	int		b_len;

	s_len = 0;
	b_len = 0;
	while (*stash != NULL && (*stash)[s_len] != '\0')
		s_len++;
	while (buf[b_len] != '\0')
		b_len++;
	tmp = malloc(sizeof(char) * (s_len + b_len + 1));
	if (!tmp)
		return (1);
	tmp[s_len + b_len] = '\0';
	while (b_len-- > 0)
		tmp[s_len + b_len] = buf[b_len];
	while (s_len-- > 0)
		tmp[s_len] = (*stash)[s_len];
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
