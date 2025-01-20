/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:50:32 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/20 18:56:47 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	change_result(t_node *node, char **result, int *n)
{
	char	*tmp_2;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (node->content[i])
	{
		if ((node->content[i] == '|' || node->content[i] == '<' || node->content[i] == '>') && node->type == 2)
		{
			*n = 1;
			break ;
		}
		i++;
	}
	tmp = malloc(sizeof(char) * (i + 1));
	j = 0;
	while (j < i)
	{
		tmp[j] = node->content[j];
		j++;
	}
	tmp[j] = '\0';
	tmp_2 = *result;
	*result = ft_strjoin(tmp_2, tmp);
	free(tmp_2);
	free(tmp);
}

static char	*echo_return(t_list *lst, int flag)
{
	char	*result;
	t_node	*node;
	char	*tmp;
	int		n;

	n = 0;
	result = ft_strdup("");
	while (lst)
	{
		node = lst->content;
		change_result(node, &result, &n);
		if (!lst->next || n == 1)
			break ;
		lst = lst->next;
	}
	if (flag == 0)
	{
		tmp = result;
		result = ft_strjoin(tmp, "\n");
		free(tmp);
	}
	return (result);
}

char	*echo_command(t_head *head)
{
	t_head	*head_tmp;
	int		tmp_2;
	int		flag;
	int		tmp;
	char	*result;

	flag = 0;
	tmp = check_equal("echo", head, 0);
	if (tmp >= 0)
	{
		tmp_2 = tmp;
		tmp = check_equal("-n", head, tmp);
		if (tmp >= 0)
			flag = 1;
		else
			tmp = tmp_2;
		head_tmp = return_head(head, tmp);
		result = echo_return(head_tmp->head, flag);
		free(head_tmp);
		return (result);
	}
	return (NULL);
}
