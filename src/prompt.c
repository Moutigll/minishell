/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:41:44 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/31 14:15:43 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*verif_solo(char *path, t_main *main)
{
	char	*result;

	if (ft_strcmp((const char *)path, (const char *)"/ ") == 0)
	{
		result = malloc(sizeof(char) * 4);
		if (!result)
			exit_on_error(main, MALLOC_ERROR);
		result[0] = '/';
		result[1] = '$';
		result[2] = ' ';
		result[3] = '\0';
		free(path);
		return (result);
	}
	return (path);
}

static char	*return_join(char *str1, char *str2, char *path, t_main *main)
{
	char	*str_final;
	char	*dest;

	if (ft_strcmp((const char *)path, (const char *)"/home") == 0
		|| return_slash(path) <= 1)
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

static char	*prompt_return(char *path, t_main *main)
{
	char	*end_user;
	char	*end_host;
	char	*user;
	char	*host;
	int		fd;

	fd = open("/etc/hostname", O_RDONLY);
	user = getenv("USER");
	end_user = ft_strjoin(user, "@");
	if (!end_user)
		exit_on_error(main, MALLOC_ERROR);
	host = get_next_line(fd);
	close(fd);
	end_host = ft_strcut(host, '.');
	free(host);
	return (return_join(end_user, end_host, path, main));
}

static char	*remove_start_prompt(char *path, t_main *main)
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
	if (!result)
		exit_on_error(main, MALLOC_ERROR);
	result[j++] = '/';
	while (i + j <= (int) ft_strlen(path) && path[i + j])
	{
		result[j] = path[i + j - 1];
		j++;
	}
	result[j++] = ' ';
	result[j] = '\0';
	free(path);
	return (verif_solo(result, main));
}

char	*read_cmd(t_main *main)
{
	char	*print_prompt;
	char	*end_path;
	char	*end_host;
	char	*path;

	path = get_env_value(main->env->envp, "PWD");
	if (path == NULL)
		path = get_env_value(main->env->envp, "HOME");
	if (!path)
		exit_on_error(main, MALLOC_ERROR);
	end_path = ft_strjoin(path, "$ ");
	if (!end_path)
		exit_on_error(main, MALLOC_ERROR);
	if (return_slash(end_path) >= 2)
		end_path = remove_start_prompt(end_path, main);
	end_host = prompt_return(path, main);
	print_prompt = ft_strjoin(end_host, end_path);
	if (!print_prompt)
		exit_on_error(main, MALLOC_ERROR);
	free(end_host);
	free(end_path);
	return (print_prompt);
}
