/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:34:36 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/13 15:50:11 by ele-lean         ###   ########.fr       */
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
	ft_putstr_fd("\033[33mWarning: PATH not found in environment, cannot proceed\033[0m\n", 2);
	return (NULL);
}

char	*check_paths(char **paths, char *cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			return ((perror("Error: Memory allocation failed for path")), NULL);
		tmp = path;
		path = ft_strjoin(path, cmd);
		free(tmp);
		if (!path)
			return (
				(perror("Error: Memory allocation failed for command path")),
				NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_putstr_fd("\033[33mWarning: Command not found in PATH: \033[0m", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}

void	resolve_command(t_command *cmd, char **paths)
{
	if (!cmd->command || ft_strlen(cmd->command) == 0)
	{
		write(STDERR_FILENO, "Error: Empty command\n", 21);
		cmd->command = NULL;
		return ;
	}
	if (cmd->command[0] == '/' || cmd->command[0] == '.')
	{
		if (access(cmd->command, X_OK) == -1)
		{
			perror("Error: Command not accessible");
			cmd->command = NULL;
			return ;
		}
	}
	else
	{
		cmd->command = check_paths(paths, cmd->command);
		if (!cmd->command)
			return ;
	}
}

void	get_path(t_pipex *pipex)
{
	char		**paths;
	t_list		*tmp;
	t_command	*cmd;

	paths = get_env_paths(pipex->cmd_head->envp);
	if (!paths)
	{
		clean_pipex(pipex, NULL, 1);
		return ;
	}
	tmp = pipex->cmd_head->head;
	while (tmp)
	{
		cmd = tmp->content;
		if (ft_strcmp(cmd->command, "echo") != 0)
			resolve_command(cmd, paths);
		tmp = tmp->next;
	}
	free_tab((void **)paths);
}
