/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:10:21 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/08 12:20:44 by ele-lean         ###   ########.fr       */
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

void	while_input(t_main **main)
{
	char	*command;
	char	*result;
	t_head	*head;

	while (1)
	{
		command = readline(read_cmd());
		if (parsing_error(command, 0))
		{
			head = sanitize_input(command);
			replace_var(&head, *main);
			exec_cmds(return_main(head, *main));
			if (ft_strlen((const char *)command) > 0)
			{
				verif_var(head, main, 0);
				// print_list((*main)->lst_var);
			}
			env_cmd(head, main);
			if (export_cmd(head, main))
				;
			result = echo_command(head);
			if (result)
				printf("%s", result);
		}
		print_list((*main)->lst_var);
		//print_block(head);
		free(command);
	}
}
