/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:52:21 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/07 02:38:29 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	open_infiles(t_pipex *pipex, int i, int read_pipe)
{
	t_list	*lst;

	lst = *pipex->cmd_head->cmds[i]->in_fd;
	while (lst && pipex->cmd_head->cmds[i]->here_doc == -1)
	{
		if (lst->next && ((t_fd_struct *)lst->content)->mode != 1)
			fake_open_infile(((t_fd_struct *)lst->content)->fd);
		else if (((t_fd_struct *)lst->content)->mode != 1)
		{
			if (!open_infile(((t_fd_struct *)lst->content)->fd))
				return (1);
		}
		lst = lst->next;
	}
	if (!(*pipex->cmd_head->cmds[i]->in_fd) && i != 0
		&& read_pipe != -1 && pipex->cmd_head->cmds[i]->here_doc == -1)
	{
		if (dup2(read_pipe, STDIN_FILENO) == -1)
		{
			perror("Error: dup2 failed for read pipe");
			return (1);
		}
	}
	return (0);
}

static int	open_outfiles(t_pipex *pipex, int i)
{
	t_list	*lst;

	lst = *pipex->cmd_head->cmds[i]->out_fd;
	while (lst)
	{
		if (lst->next)
			fake_open_outfile(((t_fd_struct *)lst->content)->fd,
				((t_fd_struct *)lst->content)->mode);
		else
		{
			if (!open_outfile(((t_fd_struct *)lst->content)->fd,
					((t_fd_struct *)lst->content)->mode))
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int	open_fds(t_pipex *pipex, int i, int read_pipe)
{
	if (open_infiles(pipex, i, read_pipe))
		return (1);
	if (read_pipe != -1)
		close(read_pipe);
	if (pipex->cmd_head->cmds[i]->here_doc != -1)
	{
		if (dup2(pipex->cmd_head->cmds[i]->here_doc, STDIN_FILENO) == -1)
		{
			perror("Error: dup2 failed for here doc");
			return (1);
		}
		close(pipex->cmd_head->cmds[i]->here_doc);
	}
	if (open_outfiles(pipex, i))
		return (1);
	return (0);
}
