/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:47:01 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/27 17:53:38 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_redirect_n(char *str, char c, char vs)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')' || str[i] == '[' || str[i] == ']')
			return (printf("Error Parentheses/Brackets not supported\n"), 1);
		else if (str[i] == c && count > 1)
			return (printf("1 Parse error near `%c'\n", c), 1);
		else if (str[i] == c && count <= 1)
			count++;
		else if (str[i] == vs && count > 0)
			return (printf("2 Parse error near `%c%c'\n", c, vs), 1);
		else if (str[i] == '|' && count > 0)
			return (printf("3 Parse error near `%c'\n", c), 1);
		else
			count = 0;
		i++;
	}
	return (0);
}

static int	check_redirect(t_list *lst)
{
	int		statement;
	t_node	*node;

	statement = 0;
	while (lst)
	{
		node = lst->content;
		if (node->type == 2 && check_pipe(node->content, &statement))
			return (printf("6 Parse error near `||'\n"), g_status = 2, 1);
		if (node->type == 2 && check_redirect_n(node->content, '>', '<') == 1)
			return (1);
		else if (node->type == 2
			&& check_redirect_n(node->content, '<', '>') == 1)
			return (1);
		if (check_brace(node->content, node->type) == 1)
			return (printf("Error bag assignment\n"), 1);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (0);
}

static char	*last_block(t_list *lst)
{
	t_node	*node;

	while (lst)
	{
		node = lst->content;
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (node->content);
}

static int	last_char(char *content, char c)
{
	int	len;

	len = (int)ft_strlen(content) - 1;
	while (len >= 0)
	{
		if ((content[len] != ' ' || content[len] != '\t')
			&& content[len] == c)
			return (1);
		else if ((content[len] != ' ' || content[len] != '\t')
			&& content[len] != c)
			return (0);
		len--;
	}
	return (0);
}

int	parse_error(t_head *head)
{
	char	*last_content;
	t_list	*lst;

	lst = head->head;
	last_content = last_block(lst);
	if (last_content == NULL)
		return (0);
	if (last_char(last_content, '|') == 1)
		return (printf("4 Parse error near `%s'\n", last_content), g_status = 2, 1);
	if (last_char(last_content, '>') == 1)
		return (printf("5 Parse error near `\\n'\n"), g_status = 2, 1);
	if (last_char(last_content, '<') == 1)
		return (printf("6 Parse error near `\\n'\n"), g_status = 2, 1);
	if (check_redirect(lst) == 1)
		return (g_status = 2, 1);
	return (0);
}
