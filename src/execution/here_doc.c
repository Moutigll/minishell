/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 01:39:38 by moutig            #+#    #+#             */
/*   Updated: 2025/02/08 15:57:40 by tle-goff         ###   ########.fr       */
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

char	*here_doc_replace_var(char *str, t_main *main)
{
	t_env_var	*var_node;
	char		*var_name;
	char		*var;
	char		*new_str;
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			var_name = extract_variable(str + i + 1);
			var_node = find_env_var_node(main->env->env_list, var_name);
			var = ft_strdup("$");
			if (str[i + 1] == '{')
				var = ft_strjoin_free(var, "{", 1, 0);
			var = ft_strjoin_free(var, var_name, 1, 0);
			if (str[i + 1] == '{')
				var = ft_strjoin_free(var, "}", 1, 0);
			if (var_node)
				new_str = ft_str_replace(str, var, var_node->value);
			else if (var_name && var_name[0] == '?' && !var_name[1])
			{
				char	*value;

				value = ft_itoa(main->error);
				new_str = ft_str_replace(str, var, value);
				free(value);
			}
			else
				new_str = ft_str_replace(str, var, "");
			free(var);
			free(var_name);
			free(str);
			str = new_str;
		}
		i++;
	}
	return (str);
}

static int	handle_here_doc(char *delimiter, t_pipex *pipex)
{
	char	*line;
	int		pipe_fd[2];
	size_t	delimiter_len;
	int		len;
	char	*new_line;

	line = NULL;
	new_line = NULL;
	if (handle_here_doc_start(pipe_fd, pipex, &delimiter_len, delimiter) == -1)
		return (-1);
	write(1, "> ", 2);
	while (1)
	{
		new_line = get_next_line(STDIN_FILENO);
		if (new_line == NULL)
		{
			if (line && new_line)
				line = ft_strjoin(line, new_line);
			else if (!line)
				return (write(1, "\n", 1), close(pipe_fd[0]), close(pipe_fd[1]), -1);
		}
		if (line && new_line)
			line = ft_strjoin_free(line, new_line, 1, 0);
		else if (new_line)
			line = new_line;
		len = ft_strlen(line);
		if (g_status == -1)
			return (close(pipe_fd[0]), close(pipe_fd[1]), -1);
		if (len > 0 && line[len - 1] == '\n')
		{
			if (ft_strncmp(line, delimiter, delimiter_len) == 0
				&& line[delimiter_len] == '\n' && line[delimiter_len + 1] == '\0')
				break ;
			write(pipe_fd[1], line, len);
			write(1, "> ", 2);
			free(line);
			line = NULL;
		}
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
