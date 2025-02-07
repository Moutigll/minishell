/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:05:41 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/07 19:43:08 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_child_process_part2(t_pipex *pipex, int i, int *pipe_fd)
{
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
		if (execve(pipex->cmd_head->cmds[i]->command[0],
				pipex->cmd_head->cmds[i]->command,
				pipex->cmd_head->main->env->envp) == -1)
			perror("Error: Failed to execute command");
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

static void	check_argument(char **args, int *status, t_pipex **pipex)
{
	if (args[1] != NULL && args[2] != NULL)
	{
		ft_putstr_fd("Error: exit: too many arguments\n", 2);
		*status = 1;
	}
	if (ft_tablen((void **)args) >= 2 && args[1][0] == '\0')
	{
		ft_putstr_fd("Error: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		(*pipex)->cmd_head->main->error = 2;
		*status = 2;
	}
}

static void	check_numeric(char **args, t_pipex **pipex, int *status, int *boolean)
{
	int	i;

	i = 0;
	if (args[1] != NULL)
	{
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				ft_putstr_fd("Error: exit: ", 2);
				ft_putstr_fd(args[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				(*pipex)->cmd_head->main->error = 2;
				*status = 2;
				break ;
			}
			else
				*boolean = 1;
			i++;
		}
	}
}

int	exit_part(t_pipex *pipex, char **args)
{
	t_command_head	*cmd_head;
	int				boolean;
	int				status;

	boolean = 0;
	cmd_head = pipex->cmd_head;
	if (!pipex->cmd_head->main->error)
		status = pipex->cmd_head->main->old_error;
	else
		status = pipex->cmd_head->main->error;
	ft_putstr_fd("exit\n", STDIN_FILENO);
	check_argument(args, &status, &pipex);
	check_numeric(args, &pipex, &status, &boolean);
	if (ft_tablen((void **)args) >= 2 && status != 1 && boolean == 1)
	{
		pipex->cmd_head->main->error = ft_atoi(args[1]);
		status = ft_atoi(args[1]);
	}
	clean_pipex(pipex, NULL, 0);
	free_total(cmd_head->main, cmd_head);
	exit(status);
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
