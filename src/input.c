/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:10:21 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/23 19:28:15 by ele-lean         ###   ########.fr       */
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

static void	exit_signal(t_main *main, char *command)
{
	printf("exit\n");
	free_tab((void **)main->g_env);
	free(main->path);
	ft_lstclear(&main->lst_var, free);
	free(main);
	free(command);
	exit(0);
}

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
			exit_signal(main, command);
		if (parsing_error(command, 0))
		{
			add_history(command);
			head = sanitize_input(command, main);
			if (ft_strlen(command) > 0)
			{
				replace_variables(head, main->env);
				reattach_head(head);
				t_head **splitted = split_head(head);
				fill_cmd(splitted[0]);
				if (splitted[1])
					fill_cmd(splitted[1]);
				//replace_var(&head, main);
				//gest_command(head, main, command);
			}
			else
				free(command);
			free_head(head);
		}
	}
}
