/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:15:31 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/28 17:19:33 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_env(t_list *lst, char **envp)
{

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
