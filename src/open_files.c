/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:02:36 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/20 01:05:52 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	open_infile(t_pipex *pipex, t_command_head *head)
{
	if (head->in_fd)
	{
		if (access(head->in_fd, R_OK) == -1)
			return (clean_pipex(pipex, "Infile is not readable", 1));
		pipex->in_fd = open(head->in_fd, O_RDONLY);
		if (pipex->in_fd == -1)
			return (clean_pipex(pipex, "Can't open infile", 1));
	}
	else
	{
		pipex->in_fd = STDIN_FILENO;
		if (pipex->in_fd == -1)
			return (clean_pipex(pipex, "Error accessing STDIN", 1));
	}
}

void	open_outfile(t_pipex *pipex, t_command_head *head)
{
	if (head->out_fd)
	{
		if (access(head->out_fd, W_OK) == -1 && access(head->out_fd, F_OK) == 0)
			return (clean_pipex(pipex, "Outfile is not writable", 1));
		pipex->out_fd = open(head->out_fd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->out_fd == -1)
			return (clean_pipex(pipex, "Can't open outfile", 1));
	}
	else
	{
		pipex->out_fd = STDOUT_FILENO;
		if (pipex->out_fd == -1)
			return (clean_pipex(pipex, "Error accessing STDOUT", 1));
	}
}


void	open_fds(t_pipex *pipex, t_command_head *head)
{
	open_infile(pipex, head);
	if (head->error)
		return ;
	open_outfile(pipex, head);
}
