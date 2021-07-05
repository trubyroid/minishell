/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:27:39 by truby             #+#    #+#             */
/*   Updated: 2021/02/04 23:16:23 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

int			get_next_line(int fd, char **line);
char		*ft_strjoin_gnl(char *s1, char *s2);
char		*ft_strdup_line(char *src);
char		*ft_strdup_rem(char *src);
int			ft_strchr_n(char *s);
int			ft_len_gnl(const char *str);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 30
#endif
