/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:34:36 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/28 15:35:03 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_env_paths(char **envp)
{
	int		index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
			return (ft_split(envp[index] + 5, ':'));
		index++;
	}
	ft_putstr_fd("\033[33mWarning: PATH not found in environment!\033[0m\n", 2);
	return (NULL);
}

char	*check_paths(char **paths, char *cmd)
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
	ft_putstr_fd("\033[33mWarning: Command not found in PATH: \033[0m", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	free(cmd);
	return (NULL);
}

void	resolve_command(t_command_struct *cmd, char **paths)
{
	if (!cmd->command || ft_strlen(cmd->command[0]) == 0)
	{
		write(STDERR_FILENO, "Error: Empty command\n", 21);
		cmd->command[0] = NULL;
		return ;
	}
	if (cmd->command[0][0] == '/' || cmd->command[0][0] == '.')
	{
		if (access(cmd->command[0], X_OK) == -1)
		{
			perror("Error: Command not accessible");
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
	char		**paths;
	t_command_struct	*cmd;
	int			i;

	paths = get_env_paths(pipex->cmd_head->main->env->envp);
	i = 0;
	while (i < pipex->cmd_head->size)
	{
		cmd = pipex->cmd_head->cmds[i];
		if (ft_strcmp(cmd->command[0], "echo") != 0
			&& ft_strcmp(cmd->command[0], "pwd") != 0
			&& ft_strcmp(cmd->command[0], "unset") != 0
			&& ft_strcmp(cmd->command[0], "export") != 0
			&& ft_strcmp(cmd->command[0], "env") != 0
			&& ft_strcmp(cmd->command[0], "cd") != 0
			&& ft_strcmp(cmd->command[0], "exit") != 0)
			resolve_command(cmd, paths);
		i++;
	}
	free_tab((void **)paths);
}
