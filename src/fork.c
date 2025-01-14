/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:05:41 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/15 15:50:04 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_child_process(t_pipex *pipex, int i, int *pipe_fd, char **envp)
{
	t_command	*cmd;
	t_command_head *head;

	head = pipex->cmd_head;
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
	close(pipex->pipe_fd[0]);
	cmd = (t_command *)ft_lstget(pipex->cmd_head->head, i)->content;
	if (pipe_fd[0] != STDIN_FILENO && pipe_fd[0] != STDOUT_FILENO)
		close(pipe_fd[0]);
	if (pipe_fd[1] != STDIN_FILENO && pipe_fd[1] != STDOUT_FILENO)
		close(pipe_fd[1]);
	i = 0;
	if (cmd->command && ft_strcmp(cmd->command, "echo") == 0)
	{
		char *l = echo_command(pipex->cmd_head->list_head);
		printf("%s", l);
		free(l);
		clean_pipex(pipex, NULL, 0);
		free_total(head->list_head, head->main);
		exit(0);
	}
	if (cmd->command && cmd->args)
	{
		if (execve(cmd->command, cmd->args, envp) == -1)
			return (clean_pipex(pipex, "Error: Failed to execute command", 1));
	}
	clean_pipex(pipex, NULL, 127);
	free_total(head->list_head, head->main);
	exit(0);
}

void	exec_cmd(t_pipex *pipex, int i, char **envp, pid_t *pid_tab)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
	{
		perror("Error: Failed to create pipe");
		return ;
	}
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
	pid_tab[i] = pid;
	close(pipe_fd[1]);
	pipex->pipe_fd[0] = pipe_fd[0];
	if (i == 0)
		close(pipex->in_fd);
	if (i == pipex->cmd_head->size - 1)
		close(pipex->out_fd);
}
