/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:02:36 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/28 18:39:11 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_infile(t_pipex *pipex, const char *infile)
{
	int	infile_fd;

	if (access(infile, R_OK) == -1)
	{
		perror("Error: Infile is not readable");
		return (-1);
	}
	infile_fd = open(infile, O_RDONLY);
	if (infile_fd == -1)
	{
		perror("Error: Can't open infile");
		return (-1);
	}
	if (dup2(infile_fd, STDIN_FILENO) == -1)
	{
		perror("Error: dup2 failed for infile");
		close(infile_fd);
		return (-1);
	}
	close(infile_fd);
	return (0);
}

int	open_outfile(const char *outfile, int mode)
{
	int	outfile_fd;
	int	flags;

	printf("Opening outfile: %s with mode: %d\n", outfile, mode);
	flags = O_WRONLY | O_CREAT;
	if (mode == 1)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	outfile_fd = open(outfile, flags, 0644);
	if (outfile_fd == -1)
	{
		perror("Error: Can't open outfile");
		return (-1);
	}
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("Error: dup2 failed for outfile");
		close(outfile_fd);
		return (-1);
	}
	return (0);
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

int	open_fds(t_pipex *pipex, int i, int read_pipe)
{
	t_list	*lst;

	lst = *pipex->cmd_head->cmds[i]->in_fd;
	while (lst && pipex->cmd_head->cmds[i]->here_doc == -1)
	{
		if (lst->next)
			fake_open_infile(((t_fd_struct *)lst->content)->fd);
		else
		{
			if (!open_infile(pipex, ((t_fd_struct *)lst->content)->fd))
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
	else if (read_pipe != -1)
		close(read_pipe);
	if (pipex->cmd_head->cmds[i]->here_doc != -1)
	{
		if (dup2(pipex->cmd_head->cmds[i]->here_doc, STDIN_FILENO) == -1)
		{
			perror("Error: dup2 failed for here doc");
			return (1);
		}
	}
	lst = *pipex->cmd_head->cmds[i]->out_fd;
	while (lst)
	{
		if (lst->next)
			fake_open_outfile(((t_fd_struct *)lst->content)->fd,
				((t_fd_struct *)lst->content)->mode);
		else
		{
			printf("Opening outfile: %s\n", ((t_fd_struct *)lst->content)->fd);
			if (!open_outfile(((t_fd_struct *)lst->content)->fd,
					((t_fd_struct *)lst->content)->mode))
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}
