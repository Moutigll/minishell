/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_take.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:33:56 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/09 19:53:35 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_tab(t_head *head)
{
	int		count;
	t_node	*node;
	t_list	*lst;
	int		i;

	count = 0;
	lst = head->head;
	while (lst)
	{
		i = 0;
		node = lst->content;
		while (node->content[i])
		{
			if (node->content[i] == '<' && node->type == 2)
				count++;
			i++;
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (count);
}

static char	*return_fd_char(t_node *content, int *boolean, char c)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (*boolean == 0)
	{
		while (content->content[i] && content->content[i] != c)
			i++;
		if (content->content[i] == c)
		{
			i++;
			*boolean = 1;
		}
	}
	if (*boolean == 1 && i > 0)
		return (NULL);
	while (content->content[i + j] && content->content[i + j] != '<' && content->content[i + j] != '>' && content->content[i + j] != '|')
		j++;
	result = malloc(sizeof(char) * (j + 1));
	j = 0;
	while (content->content[i + j] && content->content[i + j] != '<' && content->content[i + j] != '>' && content->content[i + j] != '|')
	{
		result[j] = content->content[i + j];
		j++;
	}
	if ((content->content[i + j] == '<' || content->content[i + j] == '>' || content->content[i + j] == '|') && content->type == 2)
	{
		if (content->content[i + j] == c)
			*boolean = 2;
		else
			*boolean = 3;
	}
	result[j] = '\0';
	return (result);
}

char	**return_fd(t_head *head, char c)
{
	char	**result;
	int		boolean;
	t_node	*node;
	t_list	*lst;
	int		tab;
	char	*tmp;

	tab = 0;
	boolean = 0;
	lst = head->head;
	result = malloc(sizeof(char *) * (count_tab(head) + 1));
	result[tab] = "\0";
	while (lst)
	{
		node = lst->content;
		tmp = return_fd_char(node, &boolean, c);
		if (tmp != NULL && ft_strlen(tmp) > 0)
		{
			if (node->head == 1)
				result[tab] = ft_strjoin((const char *)result[tab], (const char *)" ");
			result[tab] = ft_strjoin((const char *)result[tab], (const char *)tmp);
		}
		tmp = NULL;
		if (boolean >= 2)
		{
			tab++;
			result[tab] = "\0";
			if (boolean == 3)
				boolean = 0;
			else
				boolean = 1;
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	if (result[tab][0] != '\0')
		tab++;
	result[tab] = 0;
	return (result);
}
