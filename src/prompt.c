/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:23:56 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/13 17:00:04 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	return_slash(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '/')
			count++;
		i++;
	}
	return (count);
}

static char	*return_join(char *str1, char *str2, char *path)
{
	char	*str_final;
	char	*dest;

	if (ft_strcmp((const char *)path, (const char *)"/home") == 0
		|| return_slash(path) <= 1)
		str_final = ft_strjoin(str2, ":");
	else
		str_final = ft_strjoin(str2, ":~");
	dest = ft_strjoin(str1, str_final);
	free(str1);
	free(str2);
	free(str_final);
	return (dest);
}

char	*prompt_return(char * path)
{
	char	*end_user;
	char	*end_host;
	char	*user;
	char	*host;
	int		fd;

	fd = open("/etc/hostname", O_RDONLY);
	user = getenv("USER");
	end_user = ft_strjoin(user, "@");
	host = get_next_line(fd);
	end_host = ft_strcut(host, '.');
	free(host);
	return (return_join(end_user, end_host, path));
}
