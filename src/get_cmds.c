/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:31:37 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/23 18:10:05 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nbargs_cmd(t_list *lst)
{
	int		i;
	int		j;
	int		sep_type;
	t_node	*node;

	i = 0;
	while (lst)
	{
		node = lst->content;
		if (node->head == 1)
			i++;
		lst = lst->next;
	}
	return (i);
}

t_command_struct	*init_command_struct(t_list *head)
{
	t_command_struct	*cmd_struct;
	int					nb_args;

	nb_args = get_nbargs_cmd(head);
	cmd_struct = malloc(sizeof(t_command_struct));
	if (!cmd_struct)
		return (NULL);
	cmd_struct->command = malloc(sizeof(char *) * (nb_args + 1));
	if (!cmd_struct->command)
		return (NULL);
	cmd_struct->command[nb_args] = NULL;
	cmd_struct->in_fd = malloc(sizeof(t_list *));
	if (!cmd_struct->in_fd)
		return (NULL);
	cmd_struct->out_fd = malloc(sizeof(t_list *));
	if (!cmd_struct->out_fd)
		return (NULL);
	return (cmd_struct);
}

t_command_struct	*fill_cmd(t_head *head)
{
	t_command_struct	*cmd_struct;
	t_node				*content;
	t_list				*lst;
	char				**command;
	char				*arg;
	int					i;

	print_head(head->head);
	cmd_struct = init_command_struct(head->head);
	lst = head->head;
	i = 0;
	arg = ft_strdup("");
	command[i] = arg;
	while (lst)
	{
		content = lst->content;
		if (!content->head && content->type != 2)
			arg = ft_strjoin_free(arg, content->content, 1, 0);
		else if (content->head == 1 && content->type != 2)
		{
			i++;
			arg = ft_strdup(content->content);
			if (!arg)
				return (NULL);
			command[i] = arg;
		}
		else
		{
			int j = 0;
			int is_file = 0;
			int	file_type = 0;
			int start = 0;
			while (content->content[j] && content->content[j] != '<' && content->content[j] != '>')
				j++;
			if (j > start)
				arg = ft_strjoin_free(arg, ft_substr(content->content, start, j), 1, 1);
			if (content->content[j] == '<' || content->content[j] == '>')
			{
				while (content->content[j] && (content->content[j] == '<' || content->content[j] == '>'))
					j++;
				if (content->content[j - 2] && content->content[j - 2] == '<' || content->content[j - 2] == '>')
					file_type = 1;
				start = j;
				is_file = 1;
			}
			else if (content->content[j] == '\0')
			{
				lst = lst->next;
				content = lst->content;
				start = 0;
				j = 0;
				if (content->type == 2 && (content->content[0] == '<' || content->content[0] == '>'))
				{
					while (content->content[j] && (content->content[j] == '<' || content->content[j] == '>'))
						j++;
					if (content->content[j - 2] && content->content[j - 2] == '<' || content->content[j - 2] == '>')
						file_type = 1;
					start = j;
					is_file = 1;
				}
			}
			if (is_file)
			{
				char *filename;
				if (content->content[j])
					filename = ft_strdup(content->content + start);
				else
				{
					lst = lst->next;
					content = lst->content;
					filename = ft_strdup(content->content);
				}
				if (!filename)
					return (NULL);
				t_fd_struct	*fd_struct;
				fd_struct = malloc(sizeof(t_fd_struct));
				if (!fd_struct)
					return (NULL);
				t_list	*fd_node;
				fd_node = ft_lstnew(fd_struct);
				if (!fd_node)
					return (NULL);
				fd_struct->fd = filename;
				fd_struct->mode = file_type;
				if (content->content[j - 1] == '<')
					ft_lstadd_back(cmd_struct->in_fd, fd_node);
				else
					ft_lstadd_back(cmd_struct->out_fd, fd_node);
				lst = lst->next;
				content = lst->content;
			}
		}
		lst = lst->next;
		
	}
	printf("\n----------------------\n");
	i = 0;
	while (command[i])
	{
		printf("Arg %d: %s\n", i, command[i]);
		i++;
	}
	printf("\nFDS:\n");
	printf("IN:\n");
	t_list	*in_lst;
	while (in_lst)
	{
		t_fd_struct	*fd_struct;
		fd_struct = in_lst->content;
		printf("Mode: %d | File: %s\n", fd_struct->mode, fd_struct->fd);
		in_lst = in_lst->next;
	}
	printf("OUT:\n");
	t_list	*out_lst;
	while (out_lst)
	{
		t_fd_struct	*fd_struct;
		fd_struct = out_lst->content;
		printf("Mode: %d | File: %s\n", fd_struct->mode, fd_struct->fd);
		out_lst = out_lst->next;
	}
	return (cmd_struct);
}
