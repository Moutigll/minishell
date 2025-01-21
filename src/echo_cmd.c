/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:50:32 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/21 19:36:06 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	change_result_part1(char **result)
{
	char	*tmp;

	tmp = *result;
	*result = ft_strjoin(tmp, " ");
	free(tmp);
}

static void	change_result_part2(char *tmp, char **result, int j)
{
	char	*tmp_2;

	tmp[j] = '\0';
	tmp_2 = *result;
	*result = ft_strjoin(tmp_2, tmp);
	free(tmp_2);
	free(tmp);
}

static void	change_result(t_node *node, char **result, int *n, int k)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (node->content[i])
	{
		if ((node->content[i] == '|' || node->content[i] == '<'
				|| node->content[i] == '>') && node->type == 2)
		{
			*n = 1;
			break ;
		}
		i++;
	}
	if (node->head == 1 && k != 0 && i != 0)
		change_result_part1(result);
	tmp = malloc(sizeof(char) * (i + 1));
	j = 0;
	while (j < i)
	{
		tmp[j] = node->content[j];
		j++;
	}
	change_result_part2(tmp, result, j);
}

static char	*echo_return(t_list *lst, int flag)
{
	char	*result;
	t_node	*node;
	char	*tmp;
	int		n;
	int		i;

	i = 0;
	n = 0;
	result = ft_strdup("");
	while (lst)
	{
		node = lst->content;
		change_result(node, &result, &n, i);
		if (!lst->next || n == 1)
			break ;
		lst = lst->next;
		i++;
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
