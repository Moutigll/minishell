/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_equal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:17:53 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/19 18:38:25 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	check_block_after(t_list *lst_tmp, int *state)
{
	t_node	*node_tmp;

	if (!lst_tmp->next)
	{
		*state = 3;
		return ;
	}
	lst_tmp = lst_tmp->next;
	node_tmp = lst_tmp->content;
	if (node_tmp->head || (int)ft_strlen((const char *)node_tmp->content) == 0)
	{
		*state = 1;
		return ;
	}
	*state = 3;
}

static int	check_equal_part2(t_node *node_tmp, int *i, char *format, int *n)
{
	int		j;

	j = 0;
	while (format[*i] && node_tmp->content[j] && node_tmp->content[j] == format[*i])
	{
		(*i)++;
		j++;
	}
	if (ft_strcmp((const char *)node_tmp->content, (const char *)format) == 0 && *n == 0)
	{
		// printf("---> 1\n");
		return (4);
	}
	else if (*i == (int)ft_strlen((const char *)format) && node_tmp->content[j] == '\0')
	{
		// printf("---> 2\n");
		// printf("%s\n", node_tmp->content);
		return (4);
	}
	return (2);
}

static int	check_equal_part1(int *state, t_node *node_tmp, int *i, char *format, int *n)
{
	if (*state != 3)
	{
		*state = check_equal_part2(node_tmp, i, format, n);
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
		// if (n == 0)
		// 	printf("%s\n", node_tmp->content);
		if (state != 1 && check_equal_part1(&state, node_tmp, &i, format, &n) == 0)
			return (-2);
		if (state == 4)
			check_block_after(lst_tmp, &state);
		if (state == 3)
			return (-2);
		n++;
		if (state == 1)
			return (n + tab);
		if (!lst_tmp->next)
			break ;
		lst_tmp = lst_tmp->next;
	}
	return (-2);
}
