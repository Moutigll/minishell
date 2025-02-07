/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:22:32 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/07 00:21:28 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_slash(char *str)
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

char	*return_join(char *str1, char *str2, char *path, t_main *main)
{
	char	*str_final;
	char	*dest;

	if (ft_strcmp((const char *)path, (const char *)"/home") == 0
		|| count_slash(path) < 2)
		str_final = ft_strjoin(str2, ":");
	else
		str_final = ft_strjoin(str2, ":~");
	if (!str_final)
		exit_on_error(main, MALLOC_ERROR);
	dest = ft_strjoin(str1, str_final);
	if (!dest)
		exit_on_error(main, MALLOC_ERROR);
	free(str1);
	free(str2);
	free(str_final);
	return (dest);
}
