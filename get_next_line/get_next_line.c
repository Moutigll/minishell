/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:39:42 by tle-goff          #+#    #+#             */
/*   Updated: 2024/11/22 14:52:39 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_buffer_static(char *buffer, char **buff_reste, int i)
{
	int	j;

	if (buffer == NULL || i >= ft_strlengh(buffer))
	{
		free(*buff_reste);
		return (*buff_reste = NULL, 1);
	}
	j = ft_strlengh(&buffer[i + 0]);
	if (*buff_reste != NULL)
	{
		free(*buff_reste);
		*buff_reste = NULL;
	}
	if (j < 0)
		return (1);
	*buff_reste = (char *)malloc(sizeof(char) * (j + 1));
	if (buff_reste == NULL)
		return (0);
	j = 0;
	while (buffer[i + j] != '\0')
	{
		(*buff_reste)[j] = buffer[j + i];
		j++;
	}
	return ((*buff_reste)[j] = '\0', 1);
}

static char	*ft_buff_return(char *buff, char *b, char **buff_reste, int i)
{
	if (ft_buffer_static(b, buff_reste, i) == 0)
		return (NULL);
	free(b);
	if (*buff_reste != NULL && *buff_reste[0] == '\0')
	{
		free(*buff_reste);
		*buff_reste = NULL;
	}
	return (buff);
}

static char	*ft_line_send(char *b, char **buff_reste)
{
	char	*buff;
	int		i;

	i = 0;
	while ((b[i] != '\0' && ft_eq(b) == 0) || (b[i] != '\0' && b[i] != '\n'))
		i++;
	if (ft_eq(b) == 1)
		i++;
	buff = (char *)malloc(sizeof(char) * (i + 1));
	if (buff == NULL)
		return (NULL);
	i = 0;
	while ((b[i] != '\0' && ft_eq(b) == 0) || (b[i] != '\0' && b[i] != '\n'))
	{
		buff[i] = b[i];
		i++;
	}
	if (ft_eq(b) == 1)
		buff[i++] = '\n';
	buff[i] = '\0';
	if (b[0] == '\0')
		return (ft_free(b, buff, buff_reste));
	if (ft_eq(b) == 0)
		i++;
	return (ft_buff_return(buff, b, buff_reste, i));
}

static char	*ft_read_buffer(int fd, char *buff_t, char **buff_reste, size_t *b)
{
	char	*buff;
	int		bool;

	bool = 0;
	if (*buff_reste == NULL)
		buff = ft_strdup_b("");
	else
		buff = ft_strdup_b(*buff_reste);
	while (bool == 0 || ft_eq(buff_t) == 0)
	{
		(*b) = read(fd, buff_t, BUFFER_SIZE);
		if (buff_t != NULL && (int)(*b) > 0)
			buff_t[(*b)] = '\0';
		if ((int)(*b) == -1)
			return (free(buff), NULL);
		if ((int)(*b) == 0)
			break ;
		buff = ft_strjoin_b((char const *)buff, (char const *)buff_t);
		bool = 1;
	}
	if (buff[0] == '\0')
		return (free(buff), NULL);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff_reste;
	char		*buff_temp;
	char		*result;
	size_t		byt_read;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buff_temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff_temp == NULL)
		return (NULL);
	result = ft_read_buffer(fd, buff_temp, &buff_reste, &byt_read);
	free(buff_temp);
	if (result == NULL)
		return (NULL);
	return (ft_line_send(result, &buff_reste));
}

// int	main()
// {
// 	char	*buff;

// 	int		i = 2;
// 	int		fd;
// 	fd = open("test.txt", O_RDONLY);

// 	while (i--)
// 	{
// 		buff = get_next_line(fd);
// 		printf("%s", buff);
// 		free(buff);
// 	}
// }

// 	return (0);
// }
