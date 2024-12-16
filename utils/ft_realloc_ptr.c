/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:01:03 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/12 14:45:34 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	dest[i++] = ft_strdup(str);
	dest[i] = 0;
	free(tab);
	return (dest);
}
