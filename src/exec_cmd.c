/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:30:38 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/16 12:36:44 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_and_prepare_pipex(t_pipex **pipex, t_command_head *cmd_head)
{
	*pipex = malloc(sizeof(t_pipex));
	if (!(*pipex))
		return (clean_pipex(NULL, "Malloc error", 12));
	init_pipex(*pipex, cmd_head);
	open_fds(*pipex, cmd_head);
	if (cmd_head->here_doc && !cmd_head->error)
		handle_here_doc(cmd_head->here_doc, *pipex);
	if (!cmd_head->error)
		get_path(*pipex);
}

static pid_t	*allocate_pid_table(t_pipex *pipex, t_command_head *cmd_head)
{
	pid_t	*pid_tab;

	pid_tab = malloc(sizeof(pid_t) * cmd_head->size);
	if (!pid_tab)
		clean_pipex(pipex, "Malloc error", 12);
	return (pid_tab);
}

static void	execute_all_commands(t_pipex *pipex,
	t_command_head *cmd_head, pid_t *pid_tab)
{
	int	i;

	i = 0;
	while (i < cmd_head->size)
	{
		exec_cmd(pipex, i, cmd_head->envp, pid_tab);
		i++;
	}
}

static void	handle_waiting(t_command_head *cmd_head, pid_t *pid_tab)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	while (i < cmd_head->size)
	{
		if (waitpid(pid_tab[i], &status, 0) == -1)
			perror("Error: Failed to wait for child process");
		else if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
			if (exit_code != 0 && ((t_command *)ft_lstget(cmd_head->head,
						i)->content)->command)
			{
				ft_putstr_fd("Command ", 2);
				ft_putstr_fd(((t_command *)ft_lstget(cmd_head->head,
							i)->content)->command, 2);
				ft_putstr_fd(" PID: ", 2);
				ft_putnbr_fd(pid_tab[i], 2);
				ft_putstr_fd(" exited with status ", 2);
				cmd_head->error = exit_code;
				ft_putnbr_fd(exit_code, 2);
				ft_putstr_fd("\n", 2);
			}
		}
		i++;
	}
}

void	exec_cmds(t_command_head *cmd_head)
{
	t_pipex	*pipex;
	pid_t	*pid_tab;

	if (!cmd_head || !cmd_head->head)
		return ;
	init_and_prepare_pipex(&pipex, cmd_head);
	if (cmd_head->error || !pipex)
		return ;
	pid_tab = allocate_pid_table(pipex, cmd_head);
	if (!pid_tab)
		return ;
	execute_all_commands(pipex, cmd_head, pid_tab);
	handle_waiting(cmd_head, pid_tab);
	free(pid_tab);
	clean_pipex(pipex, NULL, 0);
}
