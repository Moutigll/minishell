/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decomp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:43:51 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/07 18:49:38 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static char	*return_command(char *command_str, int *i)
// {
// 	char	*command;
// 	int			j;

// 	j = 0;
// 	command = malloc(sizeof(t_command));
// 	while (command_str[*i + j] && command_str[*i + j] != '|')
// 		j++;
// 	command = malloc(sizeof(char) * (j + 1));
// 	j = 0;
// 	while (command_str[*i + j] && command_str[*i + j] != '|')
// 	{
// 		command[j] = command_str[*i + j];
// 		j++;
// 	}
// 	command[j++] = '\0';
// 	*i += j;
// 	return (command);
// }

static void	add_lst(t_list **lst_cmd, char *command, int n, int j)
{
	t_list	*lst;

	lst = *lst_cmd;
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	if (n == 1 && j != 0)
		lst->content = ft_strjoin((const char *)lst->content, (const char *)" ");
	lst->content = ft_strjoin((const char *)lst->content, (const char *)command);
}

static void	return_command(t_node *node, int *k, t_list **lst_cmd, int j)
{
	char	*result;
	int		tmp;
	int		i;

	i = 0;
	while (node->content[i])
	{
		if (node->content[i] == '|' && node->type == 2)
			break ;
		i++;
	}
	tmp = i;
	result = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (tmp--)
	{
		result[i] = node->content[i];
		i++;
	}
	result[i] = '\0';
	*k += i;
	add_lst(lst_cmd, result, node->head, j);
	if (node->content[i] == '|' && node->type == 2)
		ft_lstadd_back(lst_cmd, ft_lstnew("\0"));
}

static void	separated(t_head *head, t_list **lst_cmd)
{
	char	*result;
	t_node	*node;
	t_list	*lst;
	int		i;
	int		j;

	j = 0;
	result = "\0";
	lst = head->head;
	while (lst)
	{
		i = 0;
		node = lst->content;
		return_command(node, &i, lst_cmd, j);
		if (!lst->next)
			break ;
		lst = lst->next;
		j++;
	}
}

static t_command	*return_node(char *command)
{
	t_command	*cmd;
	int			i;

	i = 0;
	cmd = malloc(sizeof(t_command));
	while (command[i] && command[i] != ' ')
		i++;
	cmd->command = malloc(sizeof(char) * (i + i));
	i = 0;
	while (command[i] && command[i] != ' ')
	{
		cmd->command[i] = command[i];
		i++;
	}
	cmd->command[i] = '\0';
	cmd->args = ft_split((const char *)command, ' ');
	return (cmd);
}

static int	return_space(char *command)
{
	int	i;

	i = 0;
	while (command[i] && command[i] == ' ')
		i++;
	return (i);
}

static t_list	*return_command_main(t_list *lst_cmd)
{
	t_list	*lst_main_cmd;

	lst_main_cmd = NULL;
	while (lst_cmd)
	{
		ft_lstadd_back(&lst_main_cmd, ft_lstnew(return_node(&(lst_cmd->content)[return_space(lst_cmd->content)])));
		if (!lst_cmd->next)
			break ;
		lst_cmd = lst_cmd->next;
	}
	return (lst_main_cmd);
}

// static void	print_head(t_list *str)
// {
// 	t_command	*node;
// 	int			i;

// 	while (str)
// 	{
// 		i = 0;
// 		node = str->content;
// 		printf("Command = %s\n", node->command);
// 		while (node->args[i])
// 		{
// 			printf("Args[%i] = %s\n", i, node->args[i]);
// 			i++;
// 		}
// 		printf("\n");
// 		if (!str->next)
// 			break ;
// 		str = str->next;
// 	}

// }

t_command_head	*return_main(t_head *head, t_main *main)
{
	t_command_head	*head_main;
	t_list			*lst_cmd;

	lst_cmd = NULL;
	ft_lstadd_back(&lst_cmd, ft_lstnew("\0"));
	head_main = malloc(sizeof(t_command_head));
	head_main->in_fd = NULL;
	head_main->out_fd = NULL;
	head_main->error = 0;
	head_main->here_doc = 0;
	head_main->envp = main->g_env;
	separated(head, &lst_cmd);
	head_main->size = ft_lstsize(lst_cmd);
	head_main->head = return_command_main(lst_cmd);
	return (head_main);
}
