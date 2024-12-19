/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_equal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:17:53 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/19 15:22:48 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_equal_part2(char *content, int *i, char *format, int head, int n)
{
	int		j;

	j = 0;
	while (format[*i] && content[j] && content[j] == format[*i])
	{
		(*i)++;
		j++;
	}
	if (n == 0 && ft_strncmp((const char *)format, (const char *)content, (unsigned int)ft_strlen((const char *)content)) != 0)
		return (3);
	else if ((*i == (int)ft_strlen((const char *)format) && head && n != 0 && j == 0))
		return (1);
	else if (n == 0 && ft_strcmp((const char *)format, (const char *)content) == 0)
		return (1);
	else if ((format[*i] == '\0' || content[j] == '\0') && (format[*i] == content[j] || content[j] == '\0'))
		return (2);
	else
		return (3);
}

static int	check_equal_part1(int *state, t_node *node_tmp, int *i, char *format, int n)
{
	if (*state != 3)
	{
		*state = check_equal_part2(node_tmp->content, i, format, node_tmp->head, n);
		if (*state == 3)
			return (0);
	}
	return (1);
}

int	check_equal(char *format, t_head *head, int tab)
{
	t_node	*node_tmp;
	t_list	*lst_tmp;
	int		state;
	int		i;
	int		n;

	i = 0;
	n = 0;
	state = -1;
	lst_tmp = head->head;
	ft_listnode(&lst_tmp, tab);
	while (lst_tmp)
	{
		node_tmp = lst_tmp->content;
		if (state != 3 && state != 1 && check_equal_part1(&state, node_tmp, &i, format, n) == 0)
			return (-2);
		n++;
		if (state == 1)
			return (n);
		if (!lst_tmp->next)
			break ;
		lst_tmp = lst_tmp->next;
	}
	return (n);
}
