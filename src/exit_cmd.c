/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:00:55 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/20 20:14:23 by ele-lean         ###   ########.fr       */
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

void	free_total(t_head *head, t_main *main, t_command_head *head_main)
{
	free_tab((void **)main->g_env);
	ft_lstclear(&main->lst_var, free);
	free_head(head);
	if (main->path)
		free(main->path);
	if (head_main)
		free(head_main);
	free(main);
}

void	exit_cmd(t_head *head, t_main *main)
{
	char	*block;
	int		i;

	i = 0;
	block = attach_block(head);
	while (block[i] && block[i] != ' ')
		i++;
	if (ft_strncmp(block, "exit", 4) == 0
		&& (block[4] == '\0' || block[4] == ' '))
	{
		clear_history();
		free_total(head, main, NULL);
		free(block);
		exit(1);
	}
	free(block);
}
