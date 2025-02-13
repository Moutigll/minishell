/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:54:39 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/11 00:01:05 by tle-goff         ###   ########.fr       */
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

static char	*resolve_path(char **env, char *arg)
{
	char	*path;

	path = get_env_value(env, "HOME");
	if (!arg)
	{
		if (!path)
			ft_putstr_fd("minicoquille: cd: HOME not set\n", 2);
	}
	else if (arg[0] == '~' && path)
		path = ft_strjoin(path, arg + 1);
	else if (ft_strncmp(arg, "-", 2) == 0)
	{
		path = get_env_value(env, "OLDPWD");
		if (path)
			ft_putstr_fd(path, 1);
		else
			ft_putstr_fd("minicoquille: cd: OLDPWD not set", 2);
		ft_putstr_fd("\n", 1);
	}
	else
		return (arg);
	if (path)
		return (ft_strdup(path));
	return (NULL);
}

static int	cd_cmd_part2(char *path,
	t_envirronement *env_struct, char **args)
{
	char	*error;

	if (!args[1])
		path = resolve_path(env_struct->envp, NULL);
	else
		path = resolve_path(env_struct->envp, args[1]);
	if (!path)
		return (0);
	if (chdir(path) == -1)
	{
		error = ft_strjoin("cd: ", path);
		print_error(error);
		free(error);
		return (1);
	}
	if (path)
		free(path);
	return (0);
}

int	cd_cmd(t_envirronement *env_struct, char **args)
{
	char	*get_cwd;
	int		tab_len;
	char	*path;

	path = NULL;
	tab_len = ft_tablen((void **)args);
	if (tab_len > 2)
		return (ft_putstr_fd("minicoquille: cd: too many arguments\n", 2), 1);
	else if (args[1] && args[1][0] == '\0')
		return (0);
	if (cd_cmd_part2(path, env_struct, args) == 1)
		return (1);
	get_cwd = getcwd(NULL, 0);
	update_envlist(env_struct->env_list,
		"OLDPWD", get_env_value(env_struct->envp, "PWD"));
	if (get_cwd != NULL)
	{
		update_envlist(env_struct->env_list, "PWD", get_cwd);
		free(get_cwd);
	}
	else
		update_envlist(env_struct->env_list, "PWD", path);
	return (change_pwd(env_struct->env_list, env_struct->envp));
}
