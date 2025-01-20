/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attach.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:17:19 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/20 11:41:59 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	attach_block_quote_part_2(int i, t_node *node,
		char **result, char *c)
{
	char	*temp;

	if (node->type == i)
	{
		temp = *result;
		*result = ft_strjoin(temp, c);
		free(temp);
	}
}

static void	attach_block_quote_part_1(t_node *node, char **result)
{
	char	*temp;

	attach_block_quote_part_2(0, node, result, "\"");
	attach_block_quote_part_2(1, node, result, "\'");
	temp = *result;
	*result = ft_strjoin(temp, node->content);
	free(temp);
	attach_block_quote_part_2(0, node, result, "\"");
	attach_block_quote_part_2(1, node, result, "\'");
}

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
		attach_block_quote_part_1(node, &result);
		if (!lst->next)
			break ;
		lst = lst->next;
		i++;
	}
	return (result);
}

static void	attach_block_part_2(char **result, t_node *node)
{
	char	*temp;

	temp = *result;
	*result = ft_strjoin(temp, node->content);
	free(temp);
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
		attach_block_part_2(&result, node);
		if (!lst->next)
			break ;
		lst = lst->next;
		i++;
	}
	return (result);
}
