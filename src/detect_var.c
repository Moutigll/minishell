/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 16:32:16 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/06 11:40:21 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_var(t_node *node, int *equal)
{
	int i;

	i = 0;
	while (node->content[i])
	{
		if (!(node->content[i] >= 'a' && node->content[i] <= 'z') && !(node->content[i] >= 'A' && node->content[i] <= 'Z'))
		{
			if (node->content[i] == '=' && *equal == 0)
				(*equal)++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

static int	check_var(t_head *head)
{
	int		equal;
	t_list	*lst;
	int		i;
	t_node	*node;

	i = 0;
	equal = 0;
	lst = head->head;
	while (lst)
	{
		node = lst->content;
		if (((i == 0 && read_var(lst->content, &equal) == 0) || (i >= 1 && ft_strlen((const char *)lst->content) > 0)) && equal)
			return (i);
		if (!lst->next)
			break ;
		lst = lst->next;
		i++;
	}
	if (equal)
		return (i);
	return (-1);
}

static int	change_var(char *name_var, char *val_var, t_main **main)
{
	t_list	*lst_tmp;
	char	*var;

	lst_tmp = (*main)->lst_var;
	while (lst_tmp)
	{
		var = return_name_var(lst_tmp->content, '=');
		if (ft_strcmp((const char *)var, (const char *)name_var) == 0)
		{
			lst_tmp->content = ft_strfreejoin(name_var, val_var);
			return (0);
		}
		if (!lst_tmp->next)
			break ;
		lst_tmp = lst_tmp->next;
	}
	return (0);
}

void	verif_var(t_head *head, t_main **main)
{
	char	*name_var;
	char	*val_var;
	t_node	*rrr;
	t_node	*node;
	int		i;

	i = check_var(head);
	if (i == -1)
		return ;
	node = head->head->content;
	name_var = return_name_var(node->content, '=');
	if (i == 0)
		val_var = return_name_var(&(node->content)[ft_strlen((const char *)name_var)], '=');
	else
	{
		name_var = node->content;
		rrr = head->head->next->content;
		val_var = rrr->content;
	}
	if (change_var(name_var, val_var, main) == 0)
		ft_lstadd_back(&(*main)->lst_var, ft_lstnew(ft_strfreejoin(name_var, val_var)));
}
