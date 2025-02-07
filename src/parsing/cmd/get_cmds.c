/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:31:37 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/07 02:29:13 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redirection(t_command_struct *cmd_struct,
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

static int	is_redirection(t_list **lst, int *j, t_node *content)
{
	if (!content->content[*j])
	{
		*lst = (*lst)->next;
		*j = 0;
		return (0);
	}
	return (1);
}

static int	init_fill(t_count **count,
	t_list **lst, t_head *head, t_command_struct **cmd_struct)
{
	*cmd_struct = init_command_struct(head->head);
	*count = malloc(sizeof(t_count));
	if (!(*count))
		return (1);
	(*count)->i = -1;
	(*count)->j = 0;
	*lst = head->head;
	return (0);
}

t_command_struct	*fill_cmd(t_head *head)
{
	t_command_struct	*cmd_struct;
	t_node				*content;
	t_count				*count;
	t_list				*lst;

	init_fill(&count, &lst, head, &cmd_struct);
	while (lst)
	{
		content = lst->content;
		if ((content->type == 0 || content->type == 1)
			&& !manage_type01(content, cmd_struct, &count->i))
			return (free(count), NULL);
		else if (content->type == 2)
		{
			if (!get_start_type2(cmd_struct, content, &count->i, &count->j))
				return (free(count), NULL);
			if (!is_redirection(&lst, &count->j, content))
				continue ;
			if (!handle_redirection(cmd_struct, &content, &lst, &count->j))
				return (free(count), NULL);
			continue ;
		}
		lst = lst->next;
	}
	return (free(count), check(cmd_struct->command[0]), cmd_struct);
}
