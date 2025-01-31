/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:54:39 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/31 14:17:11 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_envlist(t_list *env, char *name, char *value)
{
	t_env_var	*env_var;

	while (env)
	{
		env_var = (t_env_var *)env->content;
		if (strcmp(env_var->name, name) == 0)
		{
			free(env_var->value);
			env_var->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
}

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

int	cd_cmd(t_envirronement *env_struct, char **args)
{
	char	*path;
	int		tab_len;

	tab_len = ft_tablen((void **)args);
	if (tab_len > 2)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	else if (args[1] && args[1][0] == '\0')
		return (0);
	if (tab_len == 1)
		path = resolve_path(env_struct->envp, "~");
	else
		path = resolve_path(env_struct->envp, args[1]);
	if (!path)
		return (0);
	printf("path = %s\n", path);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	update_envlist(env_struct->env_list, "OLDPWD", get_env_value(env_struct->envp, "PWD"));
	update_envlist(env_struct->env_list, "PWD", path);
	update_env(env_struct);
	return (0);
}
