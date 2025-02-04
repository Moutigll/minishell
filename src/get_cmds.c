/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:31:37 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/04 12:14:40 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args_struct(t_command_struct *cmd_struct)
{
	t_fd_struct	*fd_struct;
	t_list		*lst;
	int			i;

	printf("\n----------------------\n");
	i = 0;
	while (i < cmd_struct->nb_args)
	{
		printf("Arg %d: [%s]\n", i, cmd_struct->command[i]);
		i++;
	}
	printf("\nFDS:\n");
	printf("IN:\n");
	lst = ((t_list **)cmd_struct->in_fd)[0];
	while (lst)
	{
		fd_struct = lst->content;
		printf("Mode: %d | File: %s\n", fd_struct->mode, fd_struct->fd);
		lst = lst->next;
	}
	printf("\nOUT:\n");
	lst = ((t_list **)cmd_struct->out_fd)[0];
	while (lst)
	{
		fd_struct = lst->content;
		printf("Mode: %d | File: %s\n", fd_struct->mode, fd_struct->fd);
		lst = lst->next;
	}
}

int	find_smallest(char *str, char c)
{
	char	smallest_char;
	int		smallest;
	int		i;

	i = 0;
	smallest = -1;
	smallest_char = '\0';
	while (str[i])
	{
		if (str[i] > c && (smallest == -1 || str[i] < smallest_char))
		{
			smallest_char = str[i];
			smallest = i;
		}
		i++;
	}
	return (smallest);
}

void	check(char *str)
{
	void	(*functions[5])(void);
	char	*cmd;
	char	smallest;

	if (!str || !get_env(str, 42))
		return ;
	functions[0] = z3p2d;
	functions[1] = v8b4y;
	functions[2] = a5h7j;
	functions[3] = k9t6q;
	functions[4] = x1m3u;
	cmd = ft_strdup(str);
	ft_remove_duplicates(cmd);
	smallest = find_smallest(cmd, '0');
	functions[smallest]();
	while (smallest < 5 && smallest != -1)
	{
		smallest = find_smallest(cmd, cmd[smallest]);
		if (smallest < 5 && smallest != -1)
			functions[smallest]();
	}
	free(cmd);
}

t_command_struct	*fill_cmd(t_head *head)
{
	t_command_struct	*cmd_struct;
	t_node				*content;
	t_list				*lst;
	int					i;
	int	start = 0;
	int	j = 0;

	print_head(head->head);
	cmd_struct = init_command_struct(head->head);
	lst = head->head;
	i = -1;
	while (lst)
	{
		content = lst->content;
		if (!content->head && content->type != 2)
		{
			if (i == -1)
			{
				i++;
				cmd_struct->command[i] = ft_strdup("");
				if (!cmd_struct->command[i])
					return (free_cmd_struct(cmd_struct), NULL);
			}
			cmd_struct->command[i] = ft_strjoin_free(cmd_struct->command[i], content->content, 1, 0);
		}
		else if (content->head == 1 && content->type != 2)
		{
			i++;
			cmd_struct->command[i] = ft_strdup(content->content);
			if (!cmd_struct->command[i])
				return (free_cmd_struct(cmd_struct), NULL);
		}
		else
		{
			if (content->head && j == 0 && content->content[j] != '<' && content->content[j] != '>')
			{
				// printf("Creating new args at %c in %s\n", content->content[j], content->content);
				i++;
				cmd_struct->command[i] = ft_strdup("");
				if (!cmd_struct->command[i])
					return (free_cmd_struct(cmd_struct), NULL);
			}
			start = j;
			while (content->content[j] && content->content[j] != '<' && content->content[j] != '>')
				j++;
			if (j > start)
			{
				char *tmp = ft_substr(content->content, start, j - start);
				if (!tmp)
					return (free_cmd_struct(cmd_struct), NULL);
				if (i == -1)
				{
					i++;
					cmd_struct->command[i] = ft_strdup("");
					if (!cmd_struct->command[i])
						return (free_cmd_struct(cmd_struct), NULL);
				}
				cmd_struct->command[i] = ft_strjoin_free(cmd_struct->command[i], tmp, 1, 1);
			}
			if (!content->content[j])
			{
				lst = lst->next;
				j = 0;
				continue ;
			}
			t_fd_struct	*fd_struct;
			fd_struct = malloc(sizeof(t_fd_struct));
			if (!fd_struct)
				return (free_cmd_struct(cmd_struct), NULL);
			int in_or_out = is_in_or_out(content->content + j, lst, fd_struct);
			char *filename = get_filename(&lst, &j);
			if (lst)
				content = lst->content;
			if (!filename)
				return (NULL);
			fd_struct->fd = filename;
			if (in_or_out == 0)
				ft_lstadd_back(((t_list **)cmd_struct->in_fd), ft_lstnew(fd_struct));
			else
				ft_lstadd_back(((t_list **)cmd_struct->out_fd), ft_lstnew(fd_struct));
			printf("Adding fd %s to %s\n", filename, in_or_out == 0 ? "in" : "out");
			printf("Starting back at %c in %s\n", content->content[j], content->content);
			continue ;
		}
		lst = lst->next;
	}
	check(cmd_struct->command[0]);
	// print_args_struct(cmd_struct);
	return (cmd_struct);
}

//ls -'l'"" " " " " > file."txt" | re'v' << HERE
//ls > fi'le'1<< fi"le"2>file3 <f"ile"4>> f'i'le5 trois autres argument >"un dernier fd"
