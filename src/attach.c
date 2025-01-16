/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attach.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:17:19 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/16 12:09:34 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*attach_block_quote(t_head *head)
{
	char	*result;
	char	*temp;
	t_node	*node;
	t_list	*lst;
	int		i;

	i = 0;
	result = ft_strdup("");
	lst = head->head;
	while (lst)
	{
		node = lst->content;
		if (i != 0 && node->head == 1)
		{
			temp = result;
			result = ft_strjoin(temp, " ");
			free(temp);
		}
		if (node->type == 0)
		{
			temp = result;
			result = ft_strjoin(temp, "\"");
			free(temp);
		}
		if (node->type == 1)
		{
			temp = result;
			result = ft_strjoin(temp, "\'");
			free(temp);
		}
		temp = result;
		result = ft_strjoin(temp, node->content);
		free(temp);
		if (node->type == 0)
		{
			temp = result;
			result = ft_strjoin(temp, "\"");
			free(temp);
		}
		if (node->type == 1)
		{
			temp = result;
			result = ft_strjoin(temp, "\'");
			free(temp);
		}

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
	char	*temp;
	t_node	*node;
	t_list	*lst;
	int		i;

	i = 0;
	result = ft_strdup("");
	lst = head->head;
	while (lst)
	{
		node = lst->content;
		if (i != 0 && node->head == 1)
		{
			temp = result;
			result = ft_strjoin(temp, " ");
			free(temp);
		}
		temp = result;
		result = ft_strjoin(temp, node->content);
		free(temp);
		if (!lst->next)
			break ;
		lst = lst->next;
		i++;
	}
	return (result);
}
