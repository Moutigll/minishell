/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:30:38 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/28 17:17:44 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	here_doc_implement(t_command_struct *cmds, int n, int i)
{
	if (n == -1)
		return ;
	if (i == 0)
		cmds->here_doc = n;
	else
		cmds->here_doc = -1;
}

static void	check_here_doc(t_pipex	*pipex)
{
	t_command_struct	**cmds;
	t_list				*in_fd;
	int					count;
	t_fd_struct			*fd;
	int					i;

	i = -1;
	cmds = pipex->cmd_head->cmds;
	while (cmds[++i])
	{
		in_fd = cmds[i]->in_fd;
		count = ft_lstsize(in_fd) - 1;
		while (in_fd)
		{
			fd = in_fd->content;
			here_doc_implement(cmds[i],
				handle_here_doc(fd->fd, pipex), count);
			if (!in_fd->next)
				break ;
			in_fd = in_fd->next;
			count--;
		}
	}
}

static t_pipex	*init_and_prepare_pipex(t_command_head *cmd_head)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!(pipex))
		return (clean_pipex(pipex, NULL, MALLOC_ERROR), NULL);
	pipex->pid_tab = malloc(sizeof(pid_t) * cmd_head->size);
	if (!(pipex->pid_tab))
		return (clean_pipex(pipex, NULL, MALLOC_ERROR), NULL);
	pipex->cmd_head = cmd_head;
	pipex->pid_tab = NULL;
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
		if (waitpid(pipex->pid_tab[i], &status, 0) == -1)
			return ;
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_status = 128 + WTERMSIG(status);
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
	// pipex->cmd_head->cmds
	if (g_status || !pipex)
		return ;
	i = 0;
	rpipe = -1;
	while (i < pipex->cmd_head->size)
	{
		rpipe = exec_cmd(pipex, rpipe, i);
		i++;
	}
	wait_for_children(pipex);
	clean_pipex(pipex, NULL, g_status);
}
