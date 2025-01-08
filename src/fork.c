/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:05:41 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/08 13:39:48 by ele-lean         ###   ########.fr       */
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

	if (pipex->in_fd != -1 && i == 0)
		close(pipex->in_fd);
	close(pipex->stdin_backup);
	close(pipex->stdout_backup);
	cmd = (t_command *)ft_lstget(pipex->cmd_head->head, i)->content;
	if (pipe_fd[0] != STDIN_FILENO && pipe_fd[0] != STDOUT_FILENO)
		close(pipe_fd[0]);
	if (pipe_fd[1] != STDIN_FILENO && pipe_fd[1] != STDOUT_FILENO)
		close(pipe_fd[1]);
	i = 0;
	if (cmd->command && cmd->args)
	{
		if (execve(cmd->command, cmd->args, envp) == -1)
			return (clean_pipex(pipex, "Error: Failed to execute command", 1));
	}
	clean_pipex(pipex, "Error: Command not found", 127);
	exit(0);
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
	pipex->pipe_fd[0] = pipe_fd[0];
	if (i == 0)
		close(pipex->in_fd);
	if (i == pipex->cmd_head->size - 1)
		close(pipex->out_fd);
	waitpid(pid, NULL, 0);
}
