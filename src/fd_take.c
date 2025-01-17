/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_take.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:33:56 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/17 13:48:10 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_strjoin_char(char const *s1, char c)
{
	size_t	s1_len;
	size_t	i;
	char	*result;

	s1_len = ft_strlen(s1);
	result = (char *)malloc(s1_len + 2);
	if (!result)
		return (0);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i++] = c;
	result[i] = '\0';
	return (result);
}

static void	return_malloc_char_part_2(t_malloc **struc,
	char *c, char *content, char **result)
{
	while ((*struc)->boolean == 0 && c[(*struc)->j]
		&& content[(*struc)->i + (*struc)->j] == c[(*struc)->j])
	{
		(*struc)->count++;
		(*struc)->j++;
	}
	if ((*struc)->boolean == 0 && (int)ft_strlen(c) == (*struc)->count
		&& content[(*struc)->i + (*struc)->j] != c[0])
	{
		(*struc)->i += (int)ft_strlen(c);
		(*struc)->boolean = 1;
		result[(*struc)->tab] = ft_strdup("\0");
	}
	if (content[(*struc)->i + (*struc)->j] == c[0])
		(*struc)->i++;
	(*struc)->i++;
}

static void	return_malloc_char(char *content, char *c, char **result)
{
	t_malloc	*struc;

	struc = malloc(sizeof(t_malloc *));
	struc->i = 0;
	struc->tab = 0;
	struc->boolean = 0;
	while (content[struc->i])
	{
		struc->count = 0;
		struc->j = 0;
		if (struc->boolean == 1 && (content[struc->i] == '|'
				|| content[struc->i] == '<' || content[struc->i] == '>'))
		{
			struc->boolean = 0;
			struc->tab++;
		}
		else if (struc->boolean == 1)
			result[struc->tab]
				= ft_strjoin_char(result[struc->tab], content[struc->i]);
		return_malloc_char_part_2(&struc, c, content, result);
	}
}

static int	return_malloc_size(char *content, char *c)
{
	int		result;
	int		count;
	int		i;
	int		j;

	i = 0;
	result = 0;
	while (content[i])
	{
		count = 0;
		j = 0;
		while (c[j] && content[i + j] == c[j])
		{
			count++;
			j++;
		}
		if ((int)ft_strlen(c) == count && content[i + j] != c[0])
			result++;
		if (content[i + j] == c[0])
			i++;
		i++;
	}
	return (result);
}

char	**return_fd(char *content, char *c)
{
	char	**result;
	int		i;

	i = 0;
	result = ft_calloc((return_malloc_size(content, c) + 1), sizeof(char *));
	return_malloc_char(content, c, result);
	return (result);
}
