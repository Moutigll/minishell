/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:10:21 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/19 17:28:41 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	while_input(t_main **main)
{
	char	*command;
	t_head	*head;

	(void)main;
	while (1)
	{
		command = readline(read_cmd());
		if (parsing_error(command, 0))
		{
			head = sanitize_input(command);
			echo_command(head);
		}
		// print_block(sanitize_input(command));
		free(command);
	}
}
