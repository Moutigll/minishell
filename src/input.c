/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:10:21 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/21 15:55:18 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("|%s|\n", (char *)lst->content);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
}

static int	ver_void(t_list *lst)
{
	t_node	*node;
	int		count;
	int		i;

	count = 0;
	while (lst)
	{
		node = lst->content;
		i = 0;
		while (node->content[i])
		{
			if (node->content[i] != ' ')
				count++;
			i++;
		}
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	if (count > 0)
		return (1);
	return (0);
}

static int	gest_command(t_head *head, t_main *main, char *command)
{
	t_command_head	*head_main;

	if (ft_strlen((const char *)command) > 0)
		verif_var(head, main, 0);
	free(command);
	exit_cmd(head, main);
	if (ver_void(head->head) == 1)
	{
		head_main = return_main(head, main);
		exec_cmds(head_main);
		if (head_main != NULL)
			(main)->error = head_main->error;
		free(head_main);
	}
	return (0);
}

// static void	print_head(t_command_head *head_cmd)
// {
// 	printf("here_doc = %s\n", head_cmd->here_doc);
// 	printf("in_fd = %s\n", head_cmd->in_fd);
// 	printf("out_fd = %s\n", head_cmd->out_fd);
// }

void	while_input(t_main *main)
{
	char	*command;
	char	*prompt;
	t_head	*head;

	head = NULL;
	while (1)
	{
		prompt = read_cmd(main);
		command = readline(prompt);
		free(prompt);
		if (command == NULL)
		{
			printf("exit\n");
			free(command);
			exit(0);
		}
		if (parsing_error(command, 0))
		{
			add_history(command);
			head = sanitize_input(command);
			if (ft_strlen(command) > 0)
			{
				replace_var(&head, main);
				gest_command(head, main, command);
			}
			free_head(head);
		}
	}
}
