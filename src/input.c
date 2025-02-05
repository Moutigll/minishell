/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:10:21 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/05 12:53:45 by tle-goff         ###   ########.fr       */
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
	free_env(main->env->env_list);
	free(main->env);
	free(main);
	free(command);
	exit(0);
}

static void	while_input_part3(t_splitted_cmds *splitted
	, t_command_head *cmd_head, t_main *main)
{
	int	i;

	i = 0;
	while (i < splitted->size)
	{
		cmd_head->cmds[i] = fill_cmd(splitted->tab[i]);
		free_head(splitted->tab[i++]);
	}
	free(splitted->tab);
	free(splitted);
	cmd_head->main = main;
	main->error = 0;
	exec_cmds(cmd_head);
	free(cmd_head);
}

static void	while_input_part2(char *command, t_main *main)
{
	t_splitted_cmds	*splitted;
	t_command_head	*cmd_head;
	t_head			*head;

	head = sanitize_input(command, main);
	if (ft_strlen(command) > 0 && parse_error(head, main) == 0)
	{
		replace_variables(head, main);
		if (parse_error(head, main) == 0)
		{
			reattach_head(head);
			splitted = split_head(head);
			cmd_head = malloc(sizeof(t_command_head));
			if (!cmd_head)
				return ;
			cmd_head->size = splitted->size;
			cmd_head->cmds = malloc(sizeof(t_command_struct) * splitted->size);
			while_input_part3(splitted, cmd_head, main);
		}
		else
			free_head(head);
	}
	else
		free_head(head);
}

void	while_input(t_main *main)
{
	char	*command;
	char	*prompt;

	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
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
		add_history(command);
		if (parsing_error(command, 0))
			while_input_part2(command, main);
		free(command);
	}
}
