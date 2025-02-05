/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:00:55 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/05 14:09:51 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_head(t_head *head)
{
	t_list	*lst_tmp;
	t_node	*node;

	if (!head)
		return ;
	while (head->head)
	{
		node = head->head->content;
		free(node->content);
		free(node);
		lst_tmp = head->head;
		head->head = head->head->next;
		free(lst_tmp);
	}
	free(head);
}

void	free_total(t_main *main, t_command_head *head_main)
{
	free_tab((void **)main->env->envp);
	free_env(main->env->env_list);
	free(main->env);
	if (main->path)
		free(main->path);
	if (head_main)
		free(head_main);
	free(main);
}
