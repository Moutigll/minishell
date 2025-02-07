/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 01:39:38 by moutig            #+#    #+#             */
/*   Updated: 2025/02/07 02:18:11 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_here_doc_start(int pipe_fd[2],
	t_pipex *pipex, size_t *delimiter_len, char *delimiter)
{
	signal(SIGINT, signal_handler_cut);
	signal(SIGQUIT, signal_handler_cut);
	disable_ctrl_backslash_echo();
	if (pipe(pipe_fd) == -1)
		return (clean_pipex(pipex, "Pipe error", 32), -1);
	*delimiter_len = ft_strlen(delimiter);
	return (0);
}

static int	handle_here_doc(char *delimiter, t_pipex *pipex)
{
	char	*line;
	int		pipe_fd[2];
	size_t	delimiter_len;

	if (handle_here_doc_start(pipe_fd, pipex, &delimiter_len, delimiter) == -1)
		return (-1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (g_status == -1)
			return (close(pipe_fd[0]), close(pipe_fd[1]), -1);
		if (!line)
		{
			printf(ERR_HEREDOC, delimiter);
			close(pipe_fd[0]);
		}
		if ((!line) || (ft_strncmp(line, delimiter, delimiter_len) == 0
				&& line[delimiter_len] == '\n'
				&& line[delimiter_len + 1] == '\0'))
			break ;
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	if (line)
		free(line);
	return (close(pipe_fd[1]), restore_ctrl_backslash_echo(), pipe_fd[0]);
}

static int	get_here_doc(t_command_struct *cmd, t_pipex *pipex)
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
				return (-1);
			cmd->here_doc = handle_here_doc(content->fd, pipex);
			if (cmd->here_doc == -1)
			{
				pipex->cmd_head->main->error = 130;
				g_status = 0;
				return (-1);
			}
			if (lst->next)
				close(cmd->here_doc);
		}
		lst = lst->next;
	}
	return (0);
}

int	check_here_doc(t_pipex	*pipex)
{
	t_command_struct	**cmds;
	int					i;

	i = 0;
	cmds = pipex->cmd_head->cmds;
	while (i < pipex->cmd_head->size)
	{
		if (get_here_doc(cmds[i], pipex) == -1)
			return (-1);
		i++;
	}
	return (0);
}
