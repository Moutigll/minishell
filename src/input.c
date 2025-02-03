/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:10:21 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/03 12:34:13 by tle-goff         ###   ########.fr       */
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

static void	exit_signal(t_main *main, char *command)
{
	printf("exit\n");
	free_tab((void **)main->env->envp);
	free(main->path);
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
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		if (g_status == 1)
		{
			g_status = 0;
			main->error = 130;
		}
		prompt = read_cmd(main);
		command = readline(prompt);
		free(prompt);
		if (command == NULL)
			exit_signal(main, command);
		if (parsing_error(command, 0))
		{
			add_history(command);
			head = sanitize_input(command, main);
			// char *args[] = {"export", "oui=non", "5oui=", NULL};
			// export_cmd(main->env->env_list, args);
			if (ft_strlen(command) > 0 && parse_error(head, main) == 0)
			{
				free(command);
				replace_variables(head, main->env);
				if (parse_error(head, main) == 0)
				{
					printf("OK\n");
					reattach_head(head);
					t_splitted_cmds	*splitted = split_head(head);
					t_command_head	*cmd_head = malloc(sizeof(t_command_head));
					if (!cmd_head)
						return ;
					cmd_head->size = splitted->size;
					cmd_head->cmds = malloc(sizeof(t_command_struct) * splitted->size);
					int i = 0;
					while (i < splitted->size)
					{
						cmd_head->cmds[i] = fill_cmd(splitted->tab[i]);
						free_head(splitted->tab[i]);
						i++;
					}
					free(splitted->tab);
					free(splitted);
					cmd_head->main = main;
					g_status = 0;
					exec_cmds(cmd_head);
					free(cmd_head);
					//replace_var(&head, main);
					//gest_command(head, main, command);
				}
			}
			else
				free(command);
		}
	}
}
