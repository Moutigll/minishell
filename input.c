/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:10:21 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/28 14:41:04 by tle-goff         ###   ########.fr       */
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
			char *args[] = {"pwd", "ZDOTDIR", "ZSH", "CHROME_DESKTOP", NULL};
			pwd_cmd(args);
			// unset_cmd(main->env->env_list, args);
			// export_cmd(main->env->env_list, args);
			if (ft_strlen(command) > 0 && parse_error(head) == 0)
			{
				replace_variables(head, main->env);
				reattach_head(head);
				t_splitted_cmds	*splitted = split_head(head);
				int i = 0;
				while (i < splitted->size)
				{
					free_cmd_struct(fill_cmd(splitted->tab[i]));
					i++;
				}
				//replace_var(&head, main);
				//gest_command(head, main, command);
			}
			else
				free(command);
			free_head(head);
		}
	}
}
