/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:05:41 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/10 17:19:58 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_child_process_part2(t_pipex *pipex, int i, int *pipe_fd)
{
	char	*path;

	if (i != pipex->cmd_head->size - 1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	is_func_cmd(pipex, i);
	if (pipex->cmd_head->cmds[i]->command[0])
	{
		close(pipex->stdin_backup);
		close(pipex->stdout_backup);
		path = pipex->cmd_head->cmds[i]->command[0];
		pipex->cmd_head->cmds[i]->command[0] = pipex->cmd_head->cmds[i]->path;
		if (execve(path, pipex->cmd_head->cmds[i]->command,
				pipex->cmd_head->main->env->envp) == -1)
			perror("Error: Failed to execute command");
		free(path);
	}
	return (0);
}

static void	handle_child_process(t_pipex *pipex,
		int *pipe_fd, int read_pipe, int i)
{
	t_command_head	*cmd_head;

	cmd_head = pipex->cmd_head;
	if (open_fds(pipex, i, read_pipe) == 1)
	{
		clean_pipex(pipex, NULL, 1);
		free_total(cmd_head->main, cmd_head);
		exit(1);
	}
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
	handle_child_process_part2(pipex, i, pipe_fd);
	clean_pipex(pipex, NULL, 1);
	free_total(cmd_head->main, cmd_head);
	exit(127);
}

static int	handle_special_cmds(t_pipex *pipex, int i)
{
	t_command_struct	*current_cmd;

	current_cmd = pipex->cmd_head->cmds[i];
	if (current_cmd->command != NULL && pipex->cmd_head->size == 1)
	{
		if (handle_special_cmds_func(pipex, current_cmd) == 0)
			return (0);
	}
	else
		return (0);
	return (1);
}

int	exec_cmd(t_pipex *pipex, int read_pipe, int i)
{
	int			pipe_fd[2];
	pid_t		pid;

	if (handle_special_cmds(pipex, i))
		return (-1);
	if (i != pipex->cmd_head->size - 1 && pipe(pipe_fd) == -1)
		return (perror("Error: Failed to create pipe"),
			clean_pipex(pipex, NULL, 32), -1);
	pid = fork();
	if (pid == -1)
		return (perror("Error: Failed to fork"),
			clean_pipex(pipex, NULL, MALLOC_ERROR), -1);
	if (pid == 0)
		handle_child_process(pipex, pipe_fd, read_pipe, i);
	if (pipex->cmd_head->cmds[i]->here_doc != -1)
		close(pipex->cmd_head->cmds[i]->here_doc);
	if (read_pipe != -1)
		close(read_pipe);
	pipex->pid_tab[i] = pid;
	if (i != pipex->cmd_head->size - 1)
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	return (-1);
}
