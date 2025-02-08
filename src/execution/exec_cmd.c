/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:30:38 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/08 17:37:30 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_pipex(t_pipex *pipex, char *error, int exit_status)
{
	pipex->cmd_head->main->error = exit_status;
	free(pipex->pid_tab);
	while (pipex->cmd_head->size--)
		free_cmd_struct(pipex->cmd_head->cmds[pipex->cmd_head->size]);
	free(pipex->cmd_head->cmds);
	dup2(pipex->stdin_backup, STDIN_FILENO);
	dup2(pipex->stdout_backup, STDOUT_FILENO);
	close(pipex->stdin_backup);
	close(pipex->stdout_backup);
	if (error)
		perror(error);
	free(pipex);
}

static t_pipex	*init_and_prepare_pipex(t_command_head *cmd_head)
{
	t_pipex	*pipex;
	int		i;

	pipex = malloc(sizeof(t_pipex));
	if (!(pipex))
		return (clean_pipex(pipex, NULL, MALLOC_ERROR), NULL);
	pipex->pid_tab = malloc(sizeof(pid_t) * cmd_head->size);
	if (!(pipex->pid_tab))
		return (clean_pipex(pipex, NULL, MALLOC_ERROR), NULL);
	i = 0;
	while (i < cmd_head->size)
	{
		pipex->pid_tab[i] = -1;
		i++;
	}
	pipex->cmd_head = cmd_head;
	pipex->stdin_backup = dup(STDIN_FILENO);
	pipex->stdout_backup = dup(STDOUT_FILENO);
	return (pipex);
}

static void	wait_for_children(t_pipex *pipex)
{
	int		status;
	int		i;

	i = 0;
	while (i < pipex->cmd_head->size)
	{
		if (pipex->pid_tab[i] == 0 || pipex->pid_tab[i] == -1)
		{
			i++;
			continue ;
		}
		if (waitpid(pipex->pid_tab[i], &status, 0) == -1)
			return ;
		if (WIFEXITED(status))
			pipex->cmd_head->main->error = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			pipex->cmd_head->main->error = WTERMSIG(status) + 128;
		i++;
	}
}

void	exec_cmds(t_command_head *cmd_head)
{
	t_pipex	*pipex;
	int		rpipe;
	int		i;

	if (!cmd_head || !cmd_head->cmds)
		return ;
	pipex = init_and_prepare_pipex(cmd_head);
	if (pipex->cmd_head->main->error || !pipex)
		return ;
	if (check_here_doc(pipex) == -1 || pipex->cmd_head->main->error)
		return (clean_pipex(pipex, NULL, pipex->cmd_head->main->error));
	get_path(pipex);
	if (pipex->cmd_head->main->error)
		return (clean_pipex(pipex, NULL, pipex->cmd_head->main->error));
	i = 0;
	rpipe = -1;
	while (i < pipex->cmd_head->size)
	{
		rpipe = exec_cmd(pipex, rpipe, i);
		i++;
	}
	wait_for_children(pipex);
	clean_pipex(pipex, NULL, pipex->cmd_head->main->error);
}
