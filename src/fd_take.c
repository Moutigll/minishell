/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_take.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:33:56 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/08 18:30:42 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*return_fd_char(char *content, int *i, int *bool, char c)
{
	char	*result;
	int		j;

	j = 0;
	if (*bool == 0)
	{
		while (content[*i] && content[*i] != c)
			(*i)++;
		if (content[*i] == '\0')
			return (*i = 0, "\0");
		else if (content[*i] == c)
			*bool = 1;
		(*i)++;
	}
	while (content[*i + j] && content[*i + j] != '<' && content[*i + j] != '>' && content[*i + j] != '|')
		j++;
	result = malloc(sizeof(char) * (j + 1));
	j = 0;
	while (content[*i + j] && content[*i + j] != '<' && content[*i + j] != '>' && content[*i + j] != '|')
	{
		result[j] = content[*i + j];
		j++;
	}
	result[j] = '\0';
	if (content[*i + j] == '<' || content[*i + j] == '>' || content[*i + j] == '|')
		*bool = 2;
	if (content[*i] == '\0')
		return (*i = 0, "\0");
	return (result);
}

char	*return_fd(t_head *head, char c)
{
	t_node	*content;
	char	*result;
	int		boolean;
	t_list	*lst;
	int		i;

	i = 0;
	boolean = 0;
	result = "\0";
	lst = head->head;
	while (lst)
	{
		content = lst->content;
		result = ft_strjoin((const char *)result, (const char *)return_fd_char(content->content, &i, &boolean, c));
		if (!lst->next || boolean == 2)
			break ;
		lst = lst->next;
	}
	if (ft_strlen((const char *)result) > 0)
		return (result);
	return (NULL);
}
