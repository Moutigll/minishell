/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:10:21 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/10 17:32:58 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exit_signal(t_main *main, char *command)
{
	int	error;

	error = main->error;
	printf("exit\n");
	free_tab((void **)main->env->envp);
	free(main->path);
	free_env(main->env->env_list);
	free(main->home);
	free(main->env);
	free(main);
	free(command);
	exit(error);
}

static void	get_cmds(t_splitted_cmds *splitted
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
	main->old_error = main->error;
	main->error = 0;
	signal(SIGQUIT, signal_handler);
	exec_cmds(cmd_head);
	free(cmd_head);
}

static void	tokenize_input(char *command, t_main *main)
{
	t_splitted_cmds	*splitted;
	t_command_head	*cmd_head;
	t_head			*head;

	head = sanitize_input(command, main);
	if (ft_strlen(command) > 0 && parse_error(head, main) == 0)
	{
		free(command);
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
			get_cmds(splitted, cmd_head, main);
		}
		else
			free_head(head);
	}
	else
	{
		free_head(head);
		free(command);
	}
}

void	while_input(t_main *main)
{
	char	*command;
	char	*prompt;
	int		i;

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
		i = 0;
		while (command[i] == ' ')
			i++;
		if (command[i] == '\0')
		{
			free(command);
			continue ;
		}
		add_history(command);
		if (parsing_error(command, 0))
			tokenize_input(command, main);
	}
}
