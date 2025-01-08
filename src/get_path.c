/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 08:34:36 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/08 12:45:41 by ele-lean         ###   ########.fr       */
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
			return (NULL);
		tmp = path;
		path = ft_strjoin(path, cmd);
		free(tmp);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	resolve_command(t_command *cmd, char **paths)
{
	if (!cmd->command || ft_strlen(cmd->command) == 0)
	{
		cmd->command = NULL;
		return ;
	}
	if (cmd->command[0] == '/' || cmd->command[0] == '.')
	{
		if (access(cmd->command, X_OK) == -1)
		{
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
		return (clean_pipex(pipex, "PATH not found in environment", 1));
	tmp = pipex->cmd_head->head;
	while (tmp)
	{
		cmd = tmp->content;
		resolve_command(cmd, paths);
		if (!cmd->command)
			ft_putstr_fd("\033[33mWarning: Command not found\033[0m\n", 2);
		tmp = tmp->next;
	}
	free_tab((void **)paths);
}
