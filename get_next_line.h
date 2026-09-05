/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omito <omito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 17:50:27 by omito             #+#    #+#             */
/*   Updated: 2026/09/05 12:10:07 by omito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		store_stash_rest(char **stash, int count_until_newline);
char	*strcut(char *stash, int count_until_newline);
int		strjoin(char **stash, char *buf);
int		cheak_newline(char *stash, char c, int *count_until_newline);
char	*get_next_line(int fd);

#endif
