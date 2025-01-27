/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:10:25 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/27 20:24:00 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_head	*return_head(t_head *head, int i)
{
	t_head	*new_head;
	t_list	*lst;

	lst = return_lst(head, i);
	new_head = malloc(sizeof(t_head));
	new_head->head = lst;
	new_head->size = head->size;
	return (new_head);
}

t_list	*return_lst(t_head *head, int i)
{
	t_list	*lst;
	int		n;

	n = 0;
	lst = head->head;
	while (lst && i > n)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
		n++;
	}
	return (lst);
}

int	find_block(t_head *head, int *n, char **content_block, int boolean)
{
	t_node	*node;
	t_list	*lst;
	int		i;

	i = 0;
	if (!head->head)
		return (*n = -1, -1);
	*content_block = "\0";
	lst = head->head;
	while (lst)
	{
		i++;
		node = lst->content;
		if (i - 1 != 0 && node->head == 1)
			return (i);
		if (boolean == 1)
			*content_block = ft_strjoin((const char *)*content_block,
					(const char *)node->content);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (*n = -1, -1);
}

static int	count_tab(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	export_cmd(t_list *lst, char **args )
{
	int		i;

	i = 1;
	if (ft_strcmp(args[0], "export") == 0)
	{
		if (count_tab(args) == 1)
			print_ascii_sorted(lst);
		while (args[i])
			check_type_export(args[i++], lst);
	}
	print_ascii_sorted(lst);
	g_status = 0;
	return (0);
}
