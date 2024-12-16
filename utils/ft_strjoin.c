/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:06:06 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/12 17:16:58 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	while_strjoin(char **dest, char	*str, int *i)
{
	int	j;

	j = 0;
	while (str[j])
	{
		(*dest)[*i] = str[j];
		(*i)++;
		j++;
	}
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (dest == NULL)
		return (NULL);
	while_strjoin(&dest, str1, &i);
	while_strjoin(&dest, str2, &i);
	dest[i] = '\0';
	return (dest);
}
