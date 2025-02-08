/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:02:36 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/07 22:15:01 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_infile(const char *infile)
{
	int	infile_fd;

	if (access(infile, R_OK) == -1)
	{
		print_error((char *)infile);
		return (0);
	}
	infile_fd = open(infile, O_RDONLY);
	if (infile_fd == -1)
	{
		print_error((char *)infile);
		return (0);
	}
	if (dup2(infile_fd, STDIN_FILENO) == -1)
	{
		print_error((char *)infile);
		close(infile_fd);
		return (0);
	}
	close(infile_fd);
	return (1);
}

int	open_outfile(const char *outfile, int mode)
{
	int	outfile_fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (mode == 1)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	outfile_fd = open(outfile, flags, 0644);
	if (outfile_fd == -1)
	{
		print_error((char *)outfile);
		return (0);
	}
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
	{
		print_error((char *)outfile);
		close(outfile_fd);
		return (0);
	}
	close(outfile_fd);
	return (1);
}

int	fake_open_infile(char *file)
{
	int	fd;

	if (access(file, R_OK) == -1)
		return (print_error(file), 0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error(file), 0);
	if (fd != -1 && close(fd) == -1)
		return (print_error(file), 0);
	return (1);
}

int	fake_open_outfile(char *file, int mode)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (mode == 1)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	if (access(file, W_OK) == -1)
		return (print_error(file), 0);
	fd = open(file, flags, 0644);
	if (fd == -1)
		return (print_error(file), 0);
	if (fd != -1 && close(fd) == -1)
		return (print_error(file), 0);
	return (1);
}
