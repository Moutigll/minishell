/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attach.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:17:19 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/10 13:12:28 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*attach_block_quote(t_head *head)
{
	char	*result;
	t_node	*node;
	t_list	*lst;
	int		i;

	i = 0;
	result = "\0";
	lst = head->head;
	while (lst)
	{
		node = lst->content;
		if (i != 0 && node->head == 1)
			result = ft_strjoin((const char *)result, (const char *)" ");
		if (node->type == 0)
			result = ft_strjoin((const char *)result, (const char *)"\"");
		if (node->type == 1)
			result = ft_strjoin((const char *)result, (const char *)"\'");
		result = ft_strjoin((const char *)result, (const char *)node->content);
		if (node->type == 0)
			result = ft_strjoin((const char *)result, (const char *)"\"");
		if (node->type == 1)
			result = ft_strjoin((const char *)result, (const char *)"\'");
		if (!lst->next)
			break ;
		lst = lst->next;
		i++;
	}
	return (result);
}

char	*attach_block(t_head *head)
{
	char	*result;
	t_node	*node;
	t_list	*lst;
	int		i;

	i = 0;
	result = "\0";
	lst = head->head;
	while (lst)
	{
		node = lst->content;
		if (i != 0 && node->head == 1)
			result = ft_strjoin((const char *)result, (const char *)" ");
		result = ft_strjoin((const char *)result, (const char *)node->content);
		if (!lst->next)
			break ;
		lst = lst->next;
		i++;
	}
	return (result);
}
