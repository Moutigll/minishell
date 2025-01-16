/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:02:36 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/16 12:37:02 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	open_infile(t_pipex *pipex, t_command_head *head)
{
	if (pipex->in_fd != -1)
		close(pipex->in_fd);
	if (head->in_fd)
	{
		pipex->in_fd = open(head->in_fd, O_RDONLY);
		if (pipex->in_fd == -1)
			return (clean_pipex(pipex, "Can't open infile", 11));
	}
	else
	{
		pipex->in_fd = pipex->stdin_backup;
	}
}

void	open_outfile(t_pipex *pipex, t_command_head *head)
{
	int	flags;

	if (pipex->out_fd != -1)
		close(pipex->out_fd);
	flags = O_WRONLY | O_CREAT;
	if (head->out_mode == 1)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	if (head->out_fd)
	{
		pipex->out_fd = open(head->out_fd, flags, 0644);
		if (pipex->out_fd == -1)
			clean_pipex(pipex, "Can't open outfile", 21);
	}
	else
	{
		pipex->out_fd = STDOUT_FILENO;
	}
}

void	fake_open_infile(char *file)
{
	int	fd;

	if (access(file, R_OK) == -1)
		perror("Infile is not readable");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror("Can't open infile");
	if (fd != -1 && close(fd) == -1)
		perror("Can't close infile descriptor");
}

void	fake_open_outfile(char *file, int mode)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (mode == 1)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	if (access(file, W_OK) == -1)
		perror("Error: Outfile is not writable");
	fd = open(file, flags, 0644);
	if (fd == -1)
		perror("Error: Can't open outfile");
	if (fd != -1 && close(fd) == -1)
		perror("Error: Can't close outfile descriptor");
}

void	open_fds(t_pipex *pipex, t_command_head *head)
{
	open_infile(pipex, head);
	if (head->error)
		return ;
	open_outfile(pipex, head);
}
