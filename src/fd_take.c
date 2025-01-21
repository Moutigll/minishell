/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_take.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:33:56 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/21 12:05:02 by tle-goff         ###   ########.fr       */
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

static int	return_malloc_char_part2(int *boolean,
		char **result, int tab, char *c)
{
	*boolean = 1;
	result[tab] = ft_strdup("\0");
	return ((int)ft_strlen(c));
}

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int	return_malloc_char_part1(int *boolean,
		int *tab, int i, char *content, int *in_quote)
{
	if (is_quote(content[i]))
	{
		if (*in_quote == 0)
			*in_quote = content[i];
		else if (*in_quote == content[i])
			*in_quote = 0;
	}
	if (!(*in_quote) && *boolean == 1 && (content[i] == '|' || content[i] == '<' || content[i] == '>'))
	{
		*boolean = 0;
		(*tab)++;
	}
	else if (!(*in_quote) && *boolean == 1)
		return (1);
	return (0);
}

static void	return_malloc_char(char *content, char *c, char **result)
{
	int	boolean;
	int	count;
	int	tab;
	int	i;
	int	j;
	int	in_quote;

	i = 0;
	tab = 0;
	boolean = 0;
	in_quote = 0;
	while (content[i])
	{
		count = 0;
		j = 0;
		if (return_malloc_char_part1(&boolean, &tab, i, content, &in_quote) == 1)
			result[tab] = ft_strjoin_char(result[tab], content[i]);
		while (boolean == 0 && c[j] && content[i + j] == c[j])
			j++;
		count += j;
		if (boolean == 0 && (int)ft_strlen(c) == count
			&& content[i + j] != c[0])
			i += return_malloc_char_part2(&boolean, result, tab, c);
		if (content[i + j] == c[0])
			i++;
		i++;
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
