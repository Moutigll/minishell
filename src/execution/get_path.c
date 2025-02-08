/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:34:36 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/08 19:52:19 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**get_env_paths(char **envp)
{
	int		index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
			return (ft_split(envp[index] + 5, ':'));
		index++;
	}
	return (NULL);
}

static char	*check_paths(char **paths, char *cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	if (!paths)
		return (cmd);
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			return ((perror("Error: Memory allocation failed for path")), NULL);
		tmp = path;
		path = ft_strjoin(path, cmd);
		free(tmp);
		if (!path)
			return ((perror("Error: Memory allocation failed")), NULL);
		if (access(path, X_OK) == 0)
			return ((free(cmd)), path);
		free(path);
		i++;
	}
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (free(cmd), NULL);
}

static void	resolve_command(t_command_struct *cmd, char **paths)
{
	if (!cmd->command || ft_strlen(cmd->command[0]) == 0)
	{
		ft_putstr_fd(": command not found\n", 2);
		cmd->command[0] = NULL;
		return ;
	}
	if (cmd->command[0][0] == '/' || cmd->command[0][0] == '.')
	{
		if (access(cmd->command[0], X_OK) == -1)
		{
			ft_putstr_fd(cmd->command[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			free(cmd->command[0]);
			cmd->command[0] = NULL;
			return ;
		}
	}
	else
	{
		cmd->command[0] = check_paths(paths, cmd->command[0]);
		if (!cmd->command[0])
			return ;
	}
}

void	get_path(t_pipex *pipex)
{
	char				**paths;
	t_command_struct	*cmd;
	int					i;

	paths = get_env_paths(pipex->cmd_head->main->env->envp);
	i = 0;
	while (i < pipex->cmd_head->size)
	{
		cmd = pipex->cmd_head->cmds[i];
		if (cmd->command && cmd->command[0]
			&& ft_strcmp(cmd->command[0], "echo") != 0
			&& ft_strcmp(cmd->command[0], "pwd") != 0
			&& ft_strcmp(cmd->command[0], "unset") != 0
			&& ft_strcmp(cmd->command[0], "export") != 0
			&& ft_strcmp(cmd->command[0], "env") != 0
			&& ft_strcmp(cmd->command[0], "cd") != 0
			&& ft_strcmp(cmd->command[0], "exit") != 0)
		{
			cmd->path = ft_strdup(cmd->command[0]);
			resolve_command(cmd, paths);
		}
		i++;
	}
	free_tab((void **)paths);
}
