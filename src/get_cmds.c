/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:31:37 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/24 17:43:53 by ele-lean         ###   ########.fr       */
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
	int		j;
	int		size;
	int		sep_type;
	t_node	*node;

	i = 0;
	while (lst)
	{
		node = lst->content;
		if (node->head == 1 && (node->type != 2 || (node->content[0] != '<' && node->content[0] != '>')))
			i++;
		size = ft_strlen(node->content);
		if (node->type == 2 && (node->content[size - 1] == '<' || node->content[size - 1] == '>'))
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
	printf("Nb args: %d\n", cmd_struct->nb_args);
	cmd_struct->command = malloc(sizeof(char *) * (cmd_struct->nb_args + 1));
	if (!cmd_struct->command)
		return (NULL);
	cmd_struct->command[cmd_struct->nb_args] = NULL;
	cmd_struct->in_fd = malloc(sizeof(t_list **));
	if (!cmd_struct->in_fd)
		return (NULL);
	((t_list **)cmd_struct->in_fd)[0] = NULL;
	cmd_struct->out_fd = malloc(sizeof(t_list **));
	if (!cmd_struct->out_fd)
		return (NULL);
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

char	*get_filename(t_list **lst, int *j)
{
	t_node	*node;
	char	*filename;
	int		start;

	filename = NULL;
	node = (*lst)->content;
	if (!node->content[*j])
	{
		(*lst) = (*lst)->next;
		if (!(*lst))
			return (NULL);
		node = (*lst)->content;
	}
	while (node->content[*j] && (node->content[*j] == '<' || node->content[*j] == '>'))
		(*j)++;
	if (node->content[*j])
	{
		start = *j;
		while (node->content[*j] && node->content[*j] != '<' && node->content[*j] != '>')
			(*j)++;
		filename = ft_substr(node->content, start, *j - start);
	}
	else
		filename = ft_strdup("");
	if (!filename)
		return (NULL);
	if (node->content[*j] && (node->content[*j] == '<' || node->content[*j] == '>'))
		return (filename);
	(*lst) = (*lst)->next;
	if (!(*lst))
		return (filename);
	node = (*lst)->content;
	(*j) = 0;
	while ((*lst))
	{
		if (node->type != 2)
			filename = ft_strjoin_free(filename, node->content, 1, 0);
		else
		{
			(*j) = 0;
			while (node->content[*j] && node->content[*j] != '<' && node->content[*j] != '>')
				(*j)++;
			if (node->content[*j] == '<' || node->content[*j] == '>')
			{
				filename = ft_strjoin_free(filename, ft_substr(node->content, 0, *j), 1, 1);
				break ;
			}
			filename = ft_strjoin_free(filename, node->content, 1, 0);
		}
		(*lst) = (*lst)->next;
		if (!(*lst))
			break ;
		node = (*lst)->content;
		if (node->head == 1)
			break ;
	}
	return (filename);
}

t_command_struct	*fill_cmd(t_head *head)
{
	t_command_struct	*cmd_struct;
	t_node				*content;
	t_list				*lst;
	int					i;
	int	start = 0;
	int	j = 0;

	print_head(head->head);
	cmd_struct = init_command_struct(head->head);
	lst = head->head;
	i = -1;
	while (lst)
	{
		content = lst->content;
		if (!content->head && content->type != 2)
			cmd_struct->command[i] = ft_strjoin_free(cmd_struct->command[i], content->content, 1, 0);
		else if (content->head == 1 && content->type != 2)
		{
			i++;
			cmd_struct->command[i] = ft_strdup(content->content);
			if (!cmd_struct->command[i])
				return (NULL);
		}
		else
		{
			printf("Analysing %c {%s} is after\n", content->content[j], content->content + j);
			if (content->head && j == 0)
			{
				i++;
				cmd_struct->command[i] = ft_strdup("");
				if (!cmd_struct->command[i])
					return (NULL);
			}
			start = j;
			while (content->content[j] && content->content[j] != '<' && content->content[j] != '>')
				j++;
			if (j > start)
			{
				char *tmp = ft_substr(content->content, start, j - start);
				if (!tmp)
					return (NULL);
				cmd_struct->command[i] = ft_strjoin_free(cmd_struct->command[i], tmp, 1, 1);
			}
			if (!content->content[j])
			{
				printf("Exiting node %s\n", content->content);
				lst = lst->next;
				j = 0;
				continue ;
			}
			t_fd_struct	*fd_struct;
			fd_struct = malloc(sizeof(t_fd_struct));
			if (!fd_struct)
				return (NULL);
			int in_or_out = is_in_or_out(content->content + j, lst, fd_struct);
			char *filename = get_filename(&lst, &j);
			if (!filename)
				return (NULL);
			fd_struct->fd = filename;
			if (in_or_out == 0)
				ft_lstadd_back(((t_list **)cmd_struct->in_fd), ft_lstnew(fd_struct));
			else
				ft_lstadd_back(((t_list **)cmd_struct->out_fd), ft_lstnew(fd_struct));
		//	printf("Continuing at %c {%s}\n", content->content[j], content->content + j);
			continue ;
		}
		lst = lst->next;
	}
	printf("\n----------------------\n");
	i = 0;
	while (i < cmd_struct->nb_args)
	{
		printf("Arg %d: [%s]\n", i, cmd_struct->command[i]);
		i++;
	}
	printf("\nFDS:\n");
	printf("IN:\n");
	t_list	*in_lst = ((t_list **)cmd_struct->in_fd)[0];
	while (in_lst)
	{
		t_fd_struct	*fd_struct;
		fd_struct = in_lst->content;
		printf("Mode: %d | File: %s\n", fd_struct->mode, fd_struct->fd);
		in_lst = in_lst->next;
	}
	printf("\nOUT:\n");
	t_list	*out_lst = ((t_list **)cmd_struct->out_fd)[0];
	while (out_lst)
	{
		t_fd_struct	*fd_struct;
		fd_struct = out_lst->content;
		printf("Mode: %d | File: %s\n", fd_struct->mode, fd_struct->fd);
		out_lst = out_lst->next;
	}
	return (cmd_struct);
}

//ls -'l'"" " " " " > file."txt" | re'v' << HERE