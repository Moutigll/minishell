/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:39:51 by tle-goff          #+#    #+#             */
/*   Updated: 2024/11/22 16:22:21 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include "stdio.h"
# include "unistd.h"
# include "stdlib.h"
# include <fcntl.h>

char	*get_next_line(int fd);
int		ft_eq(char *buff_temp);
char	*ft_strjoin_b(char const *s1, char const *s2);
int		ft_strlengh(char const *str);
char	*ft_strdup_b(const char *s);
void	*ft_free(char *buffer, char *buff, char **buff_reste);

#endif
