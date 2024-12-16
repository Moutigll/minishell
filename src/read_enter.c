/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_enter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:51:03 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/16 11:45:47 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*verif_solo(char *path)
{
	char	*result;

	if (ft_strcmp((const char *)path, (const char *)"/ ") == 0)
	{
		result = malloc(sizeof(char) * 4);
		result[0] = '/';
		result[1] = '$';
		result[2] = ' ';
		result[3] ='\0';
		free(path);
		return (result);
	}
	return (path);
}

static char	*remove_start_prompt(char *path)
{
	char	*result;
	int		count;
	int		i;
	int		j;

	i = 0;
	j = 0;
	count = 0;
	while (path[i] && count != 3)
	{
		if (path[i] == '/')
			count++;
		i++;
	}
	result = malloc(sizeof(char) * (ft_strlen(path) - i + 3));
	result[j++] = '/';
	while (i + j <= ft_strlen(path) && path[i + j])
	{
		result[j] = path[i + j - 1];
		j++;
	}
	result[j++] = ' ';
	result[j] = '\0';
	free(path);
	return (verif_solo(result));
}

char	*read_cmd(void)
{
	char	*print_prompt;
	char	*end_path;
	char	*end_host;
	char	*buffer;
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (NULL);
	end_path = ft_strjoin(path, "$ ");
	if (return_slash(end_path) >= 2)
		end_path = remove_start_prompt(end_path);
	end_host = prompt_return(path);
	free(path);
	print_prompt = ft_strjoin(end_host, end_path);
	free(end_host);
	free(end_path);
	buffer = readline(print_prompt);
	free(print_prompt);
	if (buffer == NULL)
		return (NULL);
	return (buffer);
}
