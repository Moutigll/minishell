/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:54:39 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/22 18:39:42 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_value(char **env, const char *key)
{
	int		i;
	size_t	key_len;

	if (!env || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

char	*resolve_path(char **env, char *arg)
{
	char	*path;

	if (!arg || ft_strncmp(arg, "~", 2) == 0)
		path = get_env_value(env, "HOME");
	else if (ft_strncmp(arg, "-", 2) == 0)
		path = get_env_value(env, "OLDPWD");
	else
		return (arg);
	if (path)
		return (ft_strdup(path));
	return (NULL);
}

int	cd_cmd(char **env, char **args)
{
	char	*path;
	int		tab_len;

	tab_len = ft_tablen((void **)args);
	if (tab_len > 2)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	else if (tab_len == 1)
		path = resolve_path(env, "~");
	else
		path = resolve_path(env, args[1]);
	if (!path)
		return (0);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

// {
// 	t_head	*head_tmp;
// 	char	*old_path;
// 	char	*path;
// 	int		tmp;
// 	int		exit_status;

// 	tmp = check_equal("cd", head, 0);
// 	exit_status = 0;
// 	if (tmp >= 0)
// 	{
// 		head_tmp = return_head(head, tmp);
// 		old_path = attach_block(head_tmp);
// 		if (!old_path || old_path[0] == '\0')
// 		{
// 			free(old_path);
// 			free(head_tmp);
// 			return (1);
// 		}
// 		path = resolve_path(env, old_path);
// 		if (chdir(path) == -1)
// 		{
// 			printf("%s: No such file or directory\n", path);
// 			exit_status = 1;
// 		}
// 		if (path != old_path)
// 			free(path);
// 		free(old_path);
// 		return ((free(head_tmp)), exit_status);
// 	}
// 	return (exit_status);
// }
