/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:05:41 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/17 14:46:28 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include "../include/minishell.h"

static void	setup_child_(t_pipex *pipex, int i, int *pipe_fd)
{
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
	if (pipe_fd[0] != STDIN_FILENO && pipe_fd[0] != STDOUT_FILENO)
		close(pipe_fd[0]);
	if (pipe_fd[1] != STDIN_FILENO && pipe_fd[1] != STDOUT_FILENO)
		close(pipe_fd[1]);
}

void	is_func_cmd(char *command,
	char **args, t_pipex *pipex, t_command_head *cmd_head)
{
	char	*string;
	int		i;

	i = 0;
	if (ft_strcmp(command, "echo") == 0)
	{
		string = echo_command(pipex->cmd_head->list_head);
		printf("%s", string);
		free(string);
		i = 1;
	}
	if (ft_strcmp(command, "pwd") == 0)
	{
		if (args[1])
			ft_putstr_fd("pwd: too many arguments\n", 2);
		else
		{
			string = getcwd(NULL, 0);
			printf("%s\n", string);
			free(string);
		}
		i = 1;
	}
	if (ft_strcmp(command, "unset") == 0)
	{
		unset_cmd(pipex->cmd_head->list_head, &pipex->cmd_head->main);
		i = 1;
	}
	if (ft_strcmp(command, "export") == 0)
	{
		export_cmd(pipex->cmd_head->list_head, &pipex->cmd_head->main);
		i = 1;
	}
	if (i == 1)
	{
		clean_pipex(pipex, NULL, 0);
		free_total(cmd_head->list_head, cmd_head->main, cmd_head);
		exit(0);
	}
}

void	handle_child_process(t_pipex *pipex, int i, int *pipe_fd)
{
	t_command		*cmd;
	t_command_head	*cmd_head;

	setup_child_(pipex, i, pipe_fd);
	cmd_head = pipex->cmd_head;
	cmd = (t_command *)ft_lstget(pipex->cmd_head->head, i)->content;
	is_func_cmd(cmd->command, cmd->args, pipex, cmd_head);
	clean_pipex(pipex, NULL, 127);
	free_total(cmd_head->list_head, cmd_head->main, cmd_head);
	exit(127);
}

void	exec_cmd(t_pipex *pipex, int i, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	(void)envp;
	if (pipe(pipe_fd) == -1)
		return (perror("Error: Failed to create pipe"),
			(void)(pipex->cmd_head->error = 32));
	pid = fork();
	if (pid == -1)
	{
		perror("Error: Failed to fork");
		pipex->cmd_head->error = 10;
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return ;
	}
	if (pid == 0)
		handle_child_process(pipex, i, pipe_fd);
	pipex->pid_tab[i] = pid;
	close(pipe_fd[1]);
	pipex->pipe_fd[0] = pipe_fd[0];
	if (i == 0)
		close(pipex->in_fd);
	if (i == pipex->cmd_head->size - 1)
		close(pipex->out_fd);
}
