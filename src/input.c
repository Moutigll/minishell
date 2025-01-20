/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:10:21 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/20 11:38:37 by tle-goff         ###   ########.fr       */
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

static int	gest_command(t_head *head, t_main **main, char *command)
{
	t_command_head	*head_main;

	if (ft_strlen((const char *)command) > 0)
		verif_var(head, main, 0);
	free(command);
	exit_cmd(head, *main);
	head_main = return_main(head, *main);
	exec_cmds(head_main);
	free(head_main);
	return (0);
}

// static void	print_head(t_command_head *head_cmd)
// {
// 	printf("here_doc = %s\n", head_cmd->here_doc);
// 	printf("in_fd = %s\n", head_cmd->in_fd);
// 	printf("out_fd = %s\n", head_cmd->out_fd);
// }

void	while_input(t_main **main)
{
	char	*command;
	char	*prompt;
	t_head	*head;

	while (1)
	{
		prompt = read_cmd();
		command = readline(prompt);
		free(prompt);
		if (parsing_error(command, 0))
		{
			add_history(command);
			head = sanitize_input(command);
			if (ft_strlen(command) > 0)
			{
				replace_var(&head, *main);
				gest_command(head, main, command);
			}
		}
		free_head(head);
	}
}
