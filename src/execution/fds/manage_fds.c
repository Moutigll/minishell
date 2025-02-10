/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:52:21 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/10 18:53:45 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*here_doc_replace_var(char *str, t_main *main)
{
	t_env_var	*var_node;
	char		*var_name;
	char		*new_str;
	char		*var;
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			var_name = extract_variable(str + i + 1);
			var_node = find_env_var_node(main->env->env_list, var_name);
			var = set_var(i, str, var_name);
			if (var_node)
				new_str = ft_str_replace(str, var, var_node->value);
			else if (var_name && var_name[0] == '?' && !var_name[1])
				new_str = replace_error(main, str, var);
			else
				new_str = ft_str_replace(str, var, "");
			str = return_new_str(var, str, var_name, new_str);
		}
		i++;
	}
	return (str);
}

int	message_here_doc(char *line, char *new_line, char *delimiter)
{
	if (new_line == NULL)
	{
		if (line && new_line)
			line = ft_strjoin(line, new_line);
		else if (!line)
		{
			write(1, "\n", 2);
			ft_putstr_fd("minicoquille: warning: here-document ", 2);
			ft_putstr_fd("finished (wanted `", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putstr_fd("')\n", 2);
			return (0);
		}
	}
	return (1);
}

static int	open_infiles(t_pipex *pipex, int i)
{
	t_list	*lst;

	lst = *pipex->cmd_head->cmds[i]->in_fd;
	while (lst && pipex->cmd_head->cmds[i]->here_doc == -1)
	{
		if (lst->next && ((t_fd_struct *)lst->content)->mode == 0)
		{
			if (!fake_open_infile(((t_fd_struct *)lst->content)->fd))
				return (1);
		}
		else if (((t_fd_struct *)lst->content)->mode == 0)
		{
			if (!open_infile(((t_fd_struct *)lst->content)->fd))
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}

static int	open_outfiles(t_pipex *pipex, int i)
{
	t_list	*lst;
	int		error;

	error = 1;
	lst = *pipex->cmd_head->cmds[i]->out_fd;
	while (lst)
	{
		if (lst->next && error == 1)
			error = fake_open_outfile(((t_fd_struct *)lst->content)->fd,
					((t_fd_struct *)lst->content)->mode);
		else
		{
			if (!open_outfile(((t_fd_struct *)lst->content)->fd,
					((t_fd_struct *)lst->content)->mode) && error == 1)
				return (1);
		}
		lst = lst->next;
	}
	if (error == 0)
		return (1);
	return (0);
}

int	open_fds(t_pipex *pipex, int i, int read_pipe)
{
	if (open_infiles(pipex, i) == 1)
		return (1);
	if (!(*pipex->cmd_head->cmds[i]->in_fd) && i != 0
		&& read_pipe != -1 && pipex->cmd_head->cmds[i]->here_doc == -1)
	{
		if (dup2(read_pipe, STDIN_FILENO) == -1)
		{
			perror("Error: dup2 failed for read pipe");
			return (1);
		}
	}
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
