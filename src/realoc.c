/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:36:07 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/16 16:29:02 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*return_before(char *content)
{
	char	*result;
	int		i;

	i = 0;
	while (content[i] && content[i] != '=')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (content[i] && content[i] != '=')
	{
		result[i] = content[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int		search_env(t_main *main, char *content)
{
	char	*tmp;
	int		i;

	i = 0;
	while (main->g_env[i])
	{
		tmp = return_before(main->g_env[i]);
		if (ft_strcmp((const char *)tmp, (const char *)content) == 0)
			return (free(tmp), i);
		free(tmp);
		i++;
	}
	return (-1);
}

char	**ft_realoc_ptr_unset(char **tab, int n)
{
	char	**dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tab[i])
		i++;
	dest = malloc(sizeof(char *) * i);
	i = 0;
	while (tab[i])
	{
		if (i != n)
			dest[j++] = tab[i];
		else
			free(tab[i]);
		i++;
	}
	dest[j] = 0;
	free(tab);
	return (dest);
}

char	**ft_realoc_ptr(char **tab, char *str)
{
	char	**dest;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	dest = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tab[i])
	{
		dest[i] = tab[i];
		i++;
	}
	dest[i++] = ft_strdup((const char *)str);
	dest[i] = 0;
	free(tab);
	return (dest);
}
