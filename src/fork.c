/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:05:41 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/07 13:37:47 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_child_process(t_pipex *pipex, int i, int *pipe_fd, char **envp)
{
	t_command	*cmd;

	if (i == 0)
		dup2(pipex->in_fd, STDIN_FILENO);
	else
		dup2(pipex->pipe_fd[0], STDIN_FILENO);
	if (i == pipex->cmd_head->size - 1)
		dup2(pipex->out_fd, STDOUT_FILENO);
	else
		dup2(pipe_fd[1], STDOUT_FILENO);

	if (pipex->pipe_fd[0] != -1)
		close(pipex->pipe_fd[0]);
	if (pipex->in_fd != -1 && i == 0)
		close(pipex->in_fd);
	close(pipex->stdin_backup);
	close(pipex->stdout_backup);
	cmd = (t_command *)ft_lstget(pipex->cmd_head->head, i)->content;
	if (cmd->command && cmd->args)
	{
		if (execve(cmd->command, cmd->args, envp) == -1)
			return (clean_pipex(pipex, "Error: Failed to execute command", 1));
	}
}

void	exec_cmd(t_pipex *pipex, int i, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (perror("Error: Failed to create pipe"));
	pid = fork();
	if (pid == -1)
	{
		perror("Error: Failed to fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return ;
	}
	if (pid == 0)
		handle_child_process(pipex, i, pipe_fd, envp);
	close(pipe_fd[1]);
	if (i > 0)
		close(pipex->pipe_fd[0]);
	pipex->pipe_fd[0] = pipe_fd[0];
	if (i == 0)
		close(pipex->in_fd);
	if (i == pipex->cmd_head->size - 1)
		close(pipex->out_fd);
	waitpid(pid, NULL, 0);
}
