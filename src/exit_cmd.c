/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:00:55 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/16 11:42:44 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_head(t_head *head)
{
	t_node	*node;
	t_list	*lst;

	lst = head->head;
	while (lst)
	{
		node = lst->content;
		free(node->content);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	ft_lstclear(&lst, free);
	free(head);
}

void	free_total(t_head *head, t_main *main)
{
	free_tab((void **)main->g_env);
	ft_lstclear(&main->lst_var, free);
	free_head(head);
}

void	exit_cmd(t_head *head, t_main *main)
{
	char	*block;
	int		i;

	i  = 0;
	block = attach_block(head);
	while (block[i] && block[i] != ' ')
		i++;
	if (ft_strncmp(block, "exit", 4) == 0 && (block[4] == '\0' || block[4] == ' '))
	{
		clear_history();
		free_total(head, main);
		free(block);
		free(main);
		exit(1);
	}
	free(block);
}
