/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omito <omito@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 14:12:52 by omito             #+#    #+#             */
/*   Updated: 2026/09/05 16:21:31 by omito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

char	*free_all(char **stash, char *buf, char *sub_buf);
int		store_stash_rest(char **stash, int count_until_newline);
char	*strcut(char *stash, int count_until_newline);
int		strjoin(char **stash, char *buf);
int		cheak_newline(char *stash, char c, int *count_until_newline);
char	*get_next_line(int fd);

#endif
