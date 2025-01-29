/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:05:41 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/29 15:07:43 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_child_process(t_pipex *pipex, int *pipe_fd, int read_pipe, int i)
{
	t_command_head	*cmd_head;

	cmd_head = pipex->cmd_head;
	if (open_fds(pipex, i, read_pipe) == 1)
	{
		clean_pipex(pipex, "Error: Failed to open file descriptors", 1);
		free_total(cmd_head->main, cmd_head);
		exit(1);
	}
	close(pipe_fd[0]);
	if (ft_lstsize(*pipex->cmd_head->cmds[i]->out_fd) == 0
		&& i != pipex->cmd_head->size - 1)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("Error: dup2 failed for write pipe");
			clean_pipex(pipex, NULL, 1);
			free_total(cmd_head->main, cmd_head);
			exit(1);
		}
	}
	is_func_cmd(pipex, i);
	if (execve(pipex->cmd_head->cmds[i]->command[0],
			pipex->cmd_head->cmds[i]->command, pipex->cmd_head->main->env->envp) == -1)
	{
		perror("Error: Failed to execute command");
		clean_pipex(pipex, NULL, 1);
		free_total(cmd_head->main, cmd_head);
		exit(127);
	}
}

static int	handle_special_cmds(t_pipex *pipex, int i)
{
	t_command_struct	*current_cmd;

	current_cmd = pipex->cmd_head->cmds[i];
	if (current_cmd->command != NULL && pipex->cmd_head->size == 1)
	{
		if (current_cmd->command[0] == NULL)
			return (0);
		else if (ft_strcmp("unset", current_cmd->command[0]) == 0)
			unset_cmd(pipex->cmd_head->main->env->env_list, current_cmd->command);
		else if (ft_strcmp("export", current_cmd->command[0]) == 0)
			export_cmd(pipex->cmd_head->main->env->env_list, current_cmd->command);
		else if (ft_strcmp("cd", current_cmd->command[0]) == 0)
			cd_cmd(pipex->cmd_head->main->env, current_cmd->command);
		else if (ft_strcmp("exit", current_cmd->command[0]) == 0)
		{
			clean_pipex(pipex, NULL, 0);
			free_total(pipex->cmd_head->main, pipex->cmd_head);
			exit(g_status);
		}
		else
			return (0);
		return (1);
	}
	return (0);
}

int	exec_cmd(t_pipex *pipex, int read_pipe, int i)
{
	int			pipe_fd[2];
	pid_t		pid;

	if (handle_special_cmds(pipex, i))
		return (-1);
	if (pipe(pipe_fd) == -1)
		return (perror("Error: Failed to create pipe"),
			g_status = 32, clean_pipex(pipex, NULL, 32), -1);
	pid = fork();
	if (pid == -1)
		return (perror("Error: Failed to fork"), g_status = MALLOC_ERROR,
			clean_pipex(pipex, NULL, MALLOC_ERROR), -1);
	if (pid == 0)
		handle_child_process(pipex, pipe_fd, read_pipe, i);
	pipex->pid_tab[i] = pid;
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
