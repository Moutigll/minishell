/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 20:52:42 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/06 10:23:18 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <string.h>

t_list	*get_file_cmd(int fd)
{
	char		*line;
	t_list		*head;
	t_command	*cmd;

	head = NULL;
	while ((line = get_next_line(fd)) && line[0] != '\n')
	{
		line[ft_strlen(line) - 1] = '\0';
		cmd = malloc(sizeof(t_command));
		cmd->command = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		line[ft_strlen(line) - 1] = '\0';
		cmd->args = ft_split(line, ' ');
		free(line);
		ft_lstadd_back(&head, ft_lstnew(cmd));
	}
	free(line);
	return (head);
}

void	make_test(int fd, char **env, int i)
{
	char			*line;
	t_command_head	*cmd_head;

	line = get_next_line(fd);
	cmd_head = malloc(sizeof(t_command_head));
	ft_printf("\nTEST (%i)\n%s", i, line);
	free(line);
	line = get_next_line(fd);
	line[ft_strlen(line) - 1] = '\0';
	if (ft_strcmp(line, "NULL") == 0)
		cmd_head->in_fd = NULL;
	else
		cmd_head->in_fd = ft_strdup(line);
	free(line);
	line = get_next_line(fd);
	line[ft_strlen(line) - 1] = '\0';
	if (ft_strcmp(line, "NULL") == 0)
		cmd_head->out_fd = NULL;
	else
		cmd_head->out_fd = ft_strdup(line);
	free(line);
	line = get_next_line(fd);
	line[ft_strlen(line) - 1] = '\0';
	if (ft_strcmp(line, "0") == 0)
		cmd_head->here_doc = NULL;
	else
		cmd_head->here_doc = ft_strdup(line);
	free(line);
	line = get_next_line(fd);
	cmd_head->size = ft_atoi(line);
	free(line);
	cmd_head->head = get_file_cmd(fd);
	cmd_head->envp = env;
	exec_cmds(cmd_head);
	free(cmd_head);
}

void	tester_cmd(char **env)
{
	int		fd;
	int		lock;
	int		i;

	i = 0;
	fd = open("tester/tester_cmd/test.txt", O_RDONLY);
	printf("\033[1;37mTester by ele-lean | 42 Le Havre | Cmd testing\033[0m\n");
	make_test(fd, env, i++);
	lock = open("tester/tester_cmd/lock", O_CREAT | O_WRONLY, 0000);
	close(lock);
	ft_printf("\n\033[0;33mFile lock without permissions created.\033[0m");
	make_test(fd, env, i++);
	make_test(fd, env, i++);
	make_test(fd, env, i++);
	if (unlink("tester/tester_cmd/lock") == -1)
	{
		perror("Error deleting file");
		exit(EXIT_FAILURE);
	}
	printf("\033[0;33mFile lock deleted successfully.\033[0m\n");
	close(fd);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	tester_cmd(env);
	return (0);
}
