/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:30:38 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/05 16:02:46 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_here_doc(t_command_struct *cmd, t_pipex *pipex)
{
	t_fd_struct	*content;
	t_list		*lst;

	lst = *cmd->in_fd;
	cmd->here_doc = -1;
	while (lst)
	{
		content = lst->content;
		if (content->mode == 1)
		{
			if (g_status == -1)
				return ;
			cmd->here_doc = handle_here_doc(content->fd, pipex);
			if (cmd->here_doc == -1)
				return ;
			if (lst->next)
				close(cmd->here_doc);
		}
		lst = lst->next;
	}
}

static void	check_here_doc(t_pipex	*pipex)
{
	t_command_struct	**cmds;
	int					i;

	i = 0;
	cmds = pipex->cmd_head->cmds;
	while (i < pipex->cmd_head->size)
	{
		get_here_doc(cmds[i], pipex);
		i++;
	}
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
	get_path(pipex);
	if (pipex->cmd_head->main->error)
		return (clean_pipex(pipex, NULL, pipex->cmd_head->main->error));
	check_here_doc(pipex);
	if (pipex->cmd_head->main->error)
		return (clean_pipex(pipex, NULL, pipex->cmd_head->main->error));
	i = 0;
	rpipe = -1;
	while (i < pipex->cmd_head->size)
	{
		printf("");
		rpipe = exec_cmd(pipex, rpipe, i);
		i++;
	}
	wait_for_children(pipex);
	clean_pipex(pipex, NULL, pipex->cmd_head->main->error);
}
