/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:10:25 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/06 11:35:24 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_head	*return_head(t_head *head, int i)
{
	t_head	*new_head;
	t_list	*lst;

	lst = return_lst(head, i);
	new_head = malloc(sizeof(t_head));
	new_head->head = lst;
	new_head->size = head->size;
	return (new_head);
}

t_list	*return_lst(t_head *head, int i)
{
	t_list	*lst;
	int		n;

	n = 0;
	lst = head->head;
	while (lst && i > n)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
		n++;
	}
	return (lst);
}

int	export_cmd(t_head *head, t_main **main)
{
	int	tmp;

	tmp = check_equal("export", head, 0);
	if (tmp >= 0)
	{
		verif_var(return_head(head, tmp), main);
		return (1);
	}
	return (0);
}
