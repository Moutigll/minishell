/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:10:21 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/09 18:39:48 by tle-goff         ###   ########.fr       */
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
	char	*result;

	result = echo_command(head);
	if (ft_strlen((const char *)command) > 0)
		verif_var(head, main, 0);
	if (env_cmd(head, main))
		return (1);
	else if (cd_cmd(head))
		return (1);
	else if (unset_cmd(head, main))
		return (1);
	else if (pwd_cmd(head))
		return (1);
	else if (result)
		return (printf("->%s", result), free(result), 1);
	else if (export_cmd(head, main))
		return (1);
	exec_cmds(return_main(head, *main));
	return (0);
}

static void	print_head(t_command_head *head_cmd)
{
	int	i;

	i = 0;
	printf("here_doc = %s\n", head_cmd->here_doc);
	// while (head_cmd->in_fd[i])
	// {
	// 	printf("in_fd = %s\n", head_cmd->in_fd[i]);
	// 	i++;
	// }
	// i = 0;
	// while (head_cmd->out_fd[i])
	// {
	// 	printf("out_fd = %s\n", head_cmd->out_fd[i]);
	// 	i++;
	// }
}

void	while_input(t_main **main)
{
	char	*command;
	t_head	*head;

	while (1)
	{
		command = readline(read_cmd());
		if (parsing_error(command, 0))
		{
			head = sanitize_input(command);
			if (ft_strlen(command) > 0)
			{
				replace_var(&head, *main);
				gest_command(head, main, command);
			}
			print_head(return_main(head, *main));
		}
		// print_list((*main)->lst_var);
		// print_block(head);
		free(command);
	}
}
