/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:34:46 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/11 16:40:46 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strcut(char *str, char c)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != c)
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		dest[j] = str[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}
