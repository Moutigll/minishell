/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:39:58 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/11 16:31:44 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_free(char *buffer, char *buff, char **buff_reste)
{
	free(buff);
	free(buffer);
	if (*buff_reste != NULL)
	{
		free(*buff_reste);
		*buff_reste = NULL;
	}
	return (NULL);
}

int	ft_strlengh(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup_b(const char *s)
{
	char	*dest;
	int		count;

	count = 0;
	while (s[count] != '\0')
		count++;
	dest = (char *)malloc(sizeof(char) * (count + 1));
	if (dest == NULL)
		return (NULL);
	count = 0;
	while (s[count] != '\0')
	{
		dest[count] = s[count];
		count++;
	}
	dest[count] = '\0';
	return (dest);
}

char	*ft_strjoin_b(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*result;

	j = ft_strlengh(s2);
	i = ft_strlengh(s1);
	result = malloc(i + j + 1);
	if (result == NULL)
		return (NULL);
	j = 0;
	while (s1[j] != '\0')
	{
		result[j] = s1[j];
		j++;
	}
	j = 0;
	free((char *)s1);
	while (s2[j] != '\0')
	{
		result[j + i] = s2[j];
		j++;
	}
	result[j + i] = '\0';
	return (result);
}

int	ft_eq(char *buff_temp)
{
	int	i;

	i = 0;
	if (buff_temp == NULL || buff_temp[0] == '\0')
		return (0);
	while (buff_temp[i] != '\0')
	{
		if (buff_temp[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
