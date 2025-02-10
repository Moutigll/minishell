/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 01:39:38 by moutig            #+#    #+#             */
/*   Updated: 2025/02/10 18:49:55 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	gest_line(char **new_line, int *pipe_fd, t_pipex *pipex)
{
	*new_line = get_next_line(STDIN_FILENO);
	if (g_status == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), -1);
	if (*new_line)
		*new_line = here_doc_replace_var(*new_line, pipex->cmd_head->main);
	return (0);
}

int	write_fd(char **line, char *delimiter, int *pipe_fd)
{
	int	delimiter_len;
	int	len;

	delimiter_len = ft_strlen(delimiter);
	len = ft_strlen(*line);
	if (len > 0 && (*line)[len - 1] == '\n')
	{
		if (ft_strncmp(*line, delimiter, delimiter_len) == 0
			&& (*line)[delimiter_len] == '\n'
				&& (*line)[delimiter_len + 1] == '\0')
			return (0);
		write(pipe_fd[1], *line, len);
		write(1, "> ", 2);
		free(*line);
		*line = NULL;
	}
	return (1);
}

static int	handle_here_doc(char *delimiter, t_pipex *pipex)
{
	char	*line;
	int		pipe_fd[2];
	char	*new_line;

	line = NULL;
	new_line = NULL;
	if (handle_here_doc_start(pipe_fd, pipex) == -1)
		return (-1);
	while (1)
	{
		if (gest_line(&new_line, pipe_fd, pipex) == -1)
			return (-1);
		if (message_here_doc(line, new_line, delimiter) == 0)
			break ;
		if (line && new_line)
			line = ft_strjoin_free(line, new_line, 1, 0);
		else if (new_line)
			line = new_line;
		if (write_fd(&line, delimiter, pipe_fd) == 0)
			break ;
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
			if (lst->next)
				close(cmd->here_doc);
			if (cmd->here_doc == -1)
			{
				pipex->cmd_head->main->error = 130;
				g_status = 0;
				return (-1);
			}
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
