/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:50:32 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/15 13:03:03 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*echo_return(t_list *lst, int flag, int tmp)
{
	char	*result;
	t_node	*node;
	int		n;

	n = 0;
	result = "\0";
	ft_listnode(&lst, tmp);
	while (lst)
	{
		node = lst->content;
		if (ft_strcmp("|", node->content) == 0)
		{
			if (flag == 0)
				result = ft_strfreejoin(result, ft_strdup("\n"));
			return (result);
		}
		if (n == 0 && (int)ft_strlen((const char *)node->content) != 0)
			result = ft_strdup(node->content);
		else
		{
			if (node->head == 1 && n != 0  && ft_strlen(node->content) != 0)
				result = ft_strjoin(result, ft_strjoin(ft_strdup(" "), ft_strdup(node->content)));
			else
				result = ft_strjoin(result, ft_strdup(node->content));
		}
		if (!lst->next)
			break ;
		lst = lst->next;
		if ((int)ft_strlen((const char *)node->content) != 0)
			n++;
	}
	if (flag == 0)
		result = ft_strfreejoin(result, ft_strdup("\n"));
	return (result);
}

char	*echo_command(t_head *head)
{
	int	tmp_2;
	int	flag;
	int	tmp;

	flag = 0;
	tmp = check_equal("echo", head, 0);
	if (tmp >= 0)
	{
		tmp_2 = tmp;
		tmp = check_equal("-n", head, tmp);
		if (tmp >= 0)
			flag = 1;
		if (tmp_2 > tmp)
			tmp = tmp_2;
		return (echo_return(head->head, flag, tmp));
	}
	return (NULL);
}
