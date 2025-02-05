/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:30:39 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/05 12:03:12 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fd_list(t_list *lst)
{
	t_fd_struct	*fd_struct;
	t_list		*tmp;

	while (lst)
	{
		fd_struct = lst->content;
		free(fd_struct->fd);
		free(fd_struct);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void	free_cmd_struct(t_command_struct *cmd)
{
	int	i;

	if (!cmd)
		return ;
	free_fd_list(((t_list **)cmd->in_fd)[0]);
	free(((t_list **)cmd->in_fd));
	free_fd_list(((t_list **)cmd->out_fd)[0]);
	free(((t_list **)cmd->out_fd));
	i = 0;
	while (i < cmd->nb_args)
	{
		free(cmd->command[i]);
		i++;
	}
	free(cmd->command);
	free(cmd);
}

int	get_nbargs_cmd(t_list *lst)
{
	int		i;
	int		size;
	t_node	*node;

	i = 0;
	while (lst)
	{
		node = lst->content;
		if (node->head == 1 && (node->type != 2
				|| (node->content[0] != '<' && node->content[0] != '>')))
			i++;
		size = ft_strlen(node->content);
		if (node->type == 2 && (node->content[size - 1] == '<'
				|| node->content[size - 1] == '>')
			&& ((t_node *)lst->next->content)->head)
			i--;
		lst = lst->next;
	}
	return (i);
}

t_command_struct	*init_command_struct(t_list *head)
{
	t_command_struct	*cmd_struct;

	cmd_struct = malloc(sizeof(t_command_struct));
	if (!cmd_struct)
		return (NULL);
	cmd_struct->nb_args = get_nbargs_cmd(head);
	cmd_struct->command = malloc(sizeof(char *) * (cmd_struct->nb_args + 1));
	if (!cmd_struct->command)
		return (free_cmd_struct(cmd_struct), NULL);
	cmd_struct->command[cmd_struct->nb_args] = NULL;
	cmd_struct->in_fd = malloc(sizeof(t_list **));
	if (!cmd_struct->in_fd)
		return (free_cmd_struct(cmd_struct), NULL);
	((t_list **)cmd_struct->in_fd)[0] = NULL;
	cmd_struct->out_fd = malloc(sizeof(t_list **));
	if (!cmd_struct->out_fd)
		return (free_cmd_struct(cmd_struct), NULL);
	((t_list **)cmd_struct->out_fd)[0] = NULL;
	return (cmd_struct);
}

int	is_in_or_out(char *str,
	t_list *list, t_fd_struct *fd_struct)
{
	t_node	*node;

	if (str[0])
	{
		if (str[1] && str[0] == str[1])
			fd_struct->mode = 1;
		else
			fd_struct->mode = 0;
		if (str[0] == '<')
			return (0);
		else
			return (1);
	}
	else
	{
		node = list->next->content;
		if (node->content[1] && node->content[0] == node->content[1])
			fd_struct->mode = 1;
		else
			fd_struct->mode = 0;
		if (node->content[0] == '<')
			return (0);
		else
			return (1);
	}
}
