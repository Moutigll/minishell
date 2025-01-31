/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:21:50 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/31 14:25:01 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_node_visited(t_list *visited, t_list *node)
{
	while (visited)
	{
		if (visited->content == node->content)
			return (1);
		visited = visited->next;
	}
	return (0);
}

t_list	*find_min_node(t_list *lst, t_list *visited)
{
	t_list		*min_node;
	t_env_var	*tmp;
	t_env_var	*tmp_2;

	min_node = NULL;
	while (lst)
	{
		if (!is_node_visited(visited, lst))
		{
			tmp = lst->content;
			if (min_node != NULL)
				tmp_2 = min_node->content;
			if (!min_node || strcmp(tmp->name, tmp_2->name) < 0)
				min_node = lst;
		}
		lst = lst->next;
	}
	return (min_node);
}

int	print_ascii_sorted(t_list *lst)
{
	t_list		*min_node;
	t_list		*current;
	t_list		*visited;
	t_env_var	*tmp;

	visited = NULL;
	min_node = find_min_node(lst, visited);
	while (min_node != NULL)
	{
		tmp = min_node->content;
		if (((int)ft_strlen(tmp->name) != 1 || tmp->name[0] != '_')
			&& tmp->exported == 1)
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		else if (((int)ft_strlen(tmp->name) != 1
				|| tmp->name[0] != '_') && tmp->exported == 0)
			printf("declare -x %s\n", tmp->name);
		current = malloc(sizeof(t_list));
		if (!current)
			return (g_status = MALLOC_ERROR, ft_lstclear(&visited, free), 0);
		current->content = min_node->content;
		current->next = visited;
		visited = current;
		min_node = find_min_node(lst, visited);
	}
	return (0);
}
