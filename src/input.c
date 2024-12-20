/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:10:21 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/20 18:08:45 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	while_input(t_main **main)
{
	char	*command;
	char	*result;
	t_head	*head;

	(void)main;
	while (1)
	{
		command = readline(read_cmd());
		if (parsing_error(command, 0))
		{
			head = sanitize_input(command);
			replace_var(&head, *main);
			result = echo_command(head);
			if (result)
				printf("%s", result);
		}
		// print_block(head);
		free(command);
	}
}
