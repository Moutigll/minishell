/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:31:37 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/05 14:42:26 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_smallest(char *str, char c)
{
	char	smallest_char;
	int		smallest;
	int		i;

	i = 0;
	smallest = -1;
	smallest_char = '\0';
	while (str[i])
	{
		if (str[i] > c && (smallest == -1 || str[i] < smallest_char))
		{
			smallest_char = str[i];
			smallest = i;
		}
		i++;
	}
	return (smallest);
}

void	check(char *str)
{
	void	(*functions[5])(void);
	char	*cmd;
	char	smallest;

	if (!str || !get_env(str, 42))
		return ;
	functions[0] = z3p2d;
	functions[1] = v8b4y;
	functions[2] = a5h7j;
	functions[3] = k9t6q;
	functions[4] = x1m3u;
	cmd = ft_strdup(str);
	ft_remove_duplicates(cmd);
	smallest = find_smallest(cmd, '0');
	functions[(int)smallest]();
	while (smallest < 5 && smallest != -1)
	{
		smallest = find_smallest(cmd, cmd[(int)smallest]);
		if (smallest < 5 && smallest != -1)
			functions[(int)smallest]();
	}
	free(cmd);
}

int	manage_type01(t_node *content, t_command_struct *cmd_struct, int *i)
{
	if (!content->head && content->type != 2)
	{
		if (*i == -1)
		{
			(*i)++;
			cmd_struct->command[*i] = ft_strdup("");
			if (!cmd_struct->command[*i])
				return (free_cmd_struct(cmd_struct), 0);
		}
		cmd_struct->command[*i] = ft_strjoin_free(
				cmd_struct->command[*i], content->content, 1, 0);
	}
	else if (content->head == 1 && content->type != 2)
	{
		(*i)++;
		cmd_struct->command[*i] = ft_strdup(content->content);
		if (!cmd_struct->command[*i])
			return (free_cmd_struct(cmd_struct), 0);
	}
	return (1);
}

int	get_start_type2(t_command_struct *cmd,
	t_node *content, int *i, int *j)
{
	char	*str;
	char	*tmp;
	int		start;

	str = content->content;
	if (content->head && *j == 0 && str[*j] != '<' && str[*j] != '>')
	{
		(*i)++;
		cmd->command[*i] = ft_strdup("");
		if (!cmd->command[*i])
			return (free_cmd_struct(cmd), 0);
	}
	start = *j;
	while (str[*j] && str[*j] != '<' && str[*j] != '>')
		(*j)++;
	if (*j > start)
	{
		tmp = ft_substr(content->content, start, *j - start);
		if (!tmp)
			return (free_cmd_struct(cmd), 0);
		if (*i == -1)
		{
			(*i)++;
			cmd->command[*i] = ft_strdup("");
			if (!cmd->command[*i])
				return (free_cmd_struct(cmd), 0);
		}
		cmd->command[*i] = ft_strjoin_free(cmd->command[*i], tmp, 1, 1);
	}
	return (1);
}

int	handle_redirection(t_command_struct *cmd_struct,
	t_node **content, t_list **lst, int *j)
{
	t_fd_struct	*fd_struct;
	int			in_or_out;
	char		*filename;

	fd_struct = malloc(sizeof(t_fd_struct));
	if (!fd_struct)
		return (free_cmd_struct(cmd_struct), 0);
	in_or_out = is_in_or_out((*content)->content + *j, *lst, fd_struct);
	filename = get_filename(lst, j);
	if (*lst)
		*content = (*lst)->content;
	if (!filename)
		return (0);
	fd_struct->fd = filename;
	if (in_or_out == 0)
		ft_lstadd_back(((t_list **)cmd_struct->in_fd), ft_lstnew(fd_struct));
	else
		ft_lstadd_back(((t_list **)cmd_struct->out_fd), ft_lstnew(fd_struct));
	return (1);
}

t_command_struct	*fill_cmd(t_head *head)
{
	t_command_struct	*cmd_struct;
	t_node				*content;
	t_list				*lst;
	int					i;
	int					j;

	cmd_struct = init_command_struct(head->head);
	lst = head->head;
	i = -1;
	j = 0;
	while (lst)
	{
		content = lst->content;
		if (content->type == 0 || content->type == 1)
		{
			if (!manage_type01(content, cmd_struct, &i))
				return (NULL);
		}
		else if (content->type == 2)
		{
			if (!get_start_type2(cmd_struct, content, &i, &j))
				return (NULL);
			if (!content->content[j])
			{
				lst = lst->next;
				j = 0;
				continue ;
			}
			if (!handle_redirection(cmd_struct, &content, &lst, &j))
				return (NULL);
			continue ;
		}
		lst = lst->next;
	}
	check(cmd_struct->command[0]);
	return (cmd_struct);
}
