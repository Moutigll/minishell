/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:58:42 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/30 17:05:28 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_pipex(t_pipex *pipex, char *error, int exit_status)
{
	t_list	*tmp;

	g_status = exit_status;
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

int	handle_here_doc(char *delimiter, t_pipex *pipex)
{
	char	*line;
	int		pipe_fd[2];
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	signal(SIGINT, signal_handler_cut);
	signal(SIGQUIT, signal_handler_cut);
	disable_ctrl_backslash_echo();
	if (pipe(pipe_fd) == -1)
		return (clean_pipex(pipex, "Pipe error", 32), -1);
	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_line(0);
		if (g_status == -1)
			break ;
		if (!line)
			printf("\nbash: warning: here-document finished (wanted `%s')\n", delimiter);
		if (!line || (ft_strncmp(line, delimiter, delimiter_len) == 0
				&& line[delimiter_len] == '\n'
				&& line[delimiter_len + 1] == '\0'))
			break ;
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	if (line)
		free(line);
	close(pipe_fd[1]);
	restore_ctrl_backslash_echo();
	return (pipe_fd[0]);
}
