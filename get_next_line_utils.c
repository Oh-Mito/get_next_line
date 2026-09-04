/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omito <omito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 19:55:46 by omito             #+#    #+#             */
/*   Updated: 2026/09/04 23:45:05 by omito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

//int	strjoin(char **stash, char *buf)
//{
//	char *tmp;
//	int	stash_length;
//	int	buf_length;
//	int	total_length;
//
//	stash_length = 0;
//	buf_length = 0;
//	while (*stash != NULL && (*stash)[stash_length] != '\0')
//		stash_length++;
//	while (buf[buf_length] != '\0')
//		buf_length++;
//	total_length = stash_length + buf_length + 1;
//	tmp = malloc(sizeof(char) * total_length);
//	if (!tmp)
//		return (1);
//	tmp[total_length - 1] = '\0';
//	total_length--;
//	while (buf_length > 0)
//	{
//		tmp[total_length - 1] = buf[buf_length - 1];
//		total_length--;
//		buf_length--;
//	}
//	while (stash_length > 0)
//	{
//		tmp[total_length - 1] = (*stash)[stash_length - 1];
//		total_length--;
//		stash_length--;
//	}
//	free(*stash);
//	*stash = tmp;
//	return (0);
//}
//
//int	main(void)
//{
//	char *s1;
//	char s2[] = "efg";
//
//	s1 = malloc(sizeof(char) * 3);
//	s1[2] = '\0';
//	s1[1] = 'b';
//	s1[0] = 'a';
//	strjoin(&s1, s2);
//	printf("%s\n", s1);
//	free(s1);
//	return (0);
//}


int	store_stash_rest(char **stash, int count_until_newline)
{
	int	stash_length;
	char *tmp;
	int	i;

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

int	main(void)
{
	char *stash;

	stash = NULL;
//	stash = malloc(sizeof(char) * 6);
//	stash[0] = 'a';
//	stash[1] = 'b';
//	stash[2] = '\n';
//	stash[3] = 'd';
//	stash[4] = 'e';
//	stash[5]= '\0';
	store_stash_rest(&stash, 0);
	printf ("%s", stash);
	free(stash);

}
