/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:30:38 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/06 14:35:46 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_pipex(t_pipex *pipex, t_command_head *cmd_head)
{
	pipex->cmd_head = cmd_head;
	pipex->in_fd = -1;
	pipex->out_fd = -1;
	pipex->pipe_fd[0] = -1;
	pipex->cmd_head = cmd_head;
	pipex->cmd_head->error = 0;
	pipex->stdin_backup = dup(STDIN_FILENO);
	pipex->stdout_backup = dup(STDOUT_FILENO);
}

void	clean_pipex(t_pipex *pipex, char *error, int exit_status)
{
	t_list	*tmp;

	pipex->cmd_head->error = exit_status;
	tmp = pipex->cmd_head->head;
	while (tmp)
	{
		free(((t_command *)tmp->content)->command);
		free_tab((void **)((t_command *)tmp->content)->args);
		tmp = tmp->next;
	}
	free_list(pipex->cmd_head->head);
	if (pipex->cmd_head->in_fd != NULL)
		free(pipex->cmd_head->in_fd);
	if (pipex->cmd_head->out_fd != NULL)
		free(pipex->cmd_head->out_fd);
	if (pipex->cmd_head->here_doc)
		free(pipex->cmd_head->here_doc);
	if (pipex->in_fd != -1 && pipex->in_fd != STDIN_FILENO)
		close(pipex->in_fd);
	if (pipex->out_fd != -1 && pipex->out_fd != STDOUT_FILENO)
		close(pipex->out_fd);
	if (pipex->pipe_fd[0] != -1 && pipex->pipe_fd[0]
		!= STDIN_FILENO && pipex->pipe_fd[0] != STDOUT_FILENO)
		close(pipex->pipe_fd[0]);
	if (error)
		perror(error);
	dup2(pipex->stdin_backup, STDIN_FILENO);
	dup2(pipex->stdout_backup, STDOUT_FILENO);
	close(pipex->stdin_backup);
	close(pipex->stdout_backup);
	free(pipex);
}

void	handle_here_doc(char *delimiter, t_pipex *pipex)
{
	char	*line;
	int		pipe_fd[2];
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	if (pipe(pipe_fd) == -1)
		clean_pipex(pipex, "Pipe error", 1);
	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_line(0);
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
	pipex->in_fd = pipe_fd[0];
}

void	exec_cmds(t_command_head *cmd_head)
{
	t_pipex		*pipex;
	int			i;

	if (!cmd_head || !cmd_head->head)
		return ;
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (clean_pipex(pipex, "Malloc error", 1));
	init_pipex(pipex, cmd_head);
	open_fds(pipex, cmd_head);
	if (cmd_head->error)
		return ;
	if (cmd_head->here_doc)
		handle_here_doc(cmd_head->here_doc, pipex);
	if (cmd_head->error)
		return ;
	get_path(pipex);
	if (cmd_head->error)
		return ;
	i = 0;
	while (i < cmd_head->size)
	{
		exec_cmd(pipex, i, cmd_head->envp);
		i++;
	}
	printf("Commands executed\n");
	clean_pipex(pipex, NULL, 0);
}
