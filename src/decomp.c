/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decomp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:43:51 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/09 19:51:13 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_delimited(const char *s, int index)
{
	int	parentheses = 0;
	int	braces = 0;
	int	brackets = 0;

	for (int i = 0; i < index; i++)
	{
		if (s[i] == '(')
			parentheses++;
		else if (s[i] == ')')
			parentheses--;
		else if (s[i] == '{')
			braces++;
		else if (s[i] == '}')
			braces--;
		else if (s[i] == '[')
			brackets++;
		else if (s[i] == ']')
			brackets--;
	}
	return (parentheses > 0 || braces > 0 || brackets > 0);
}

static int	count_words(const char *s, char c)
{
	int	count = 0;
	int	i = 0;

	while (s[i])
	{
		while (s[i] == c && !is_delimited(s, i) && s[i])
			i++;
		if (s[i])
		{
			count++;
			while ((s[i] != c || is_delimited(s, i)) && s[i])
				i++;
		}
	}
	return (count);
}

static char	*malloc_word(const char *s, char c, int *start)
{
	int		len = 0;
	char	*word;

	while (s[*start + len] && (s[*start + len] != c || is_delimited(s, *start + len)))
		len++;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	word[len] = '\0';
	for (int i = 0; i < len; i++)
		word[i] = s[*start + i];
	*start += len;
	return (word);
}

static void	free_split(char **split, int words)
{
	int	i = 0;
	while (i < words)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	fill_array(const char *s, char c, char **split)
{
	int	index = 0;
	int	i = 0;

	while (s[i])
	{
		while (s[i] == c && !is_delimited(s, i) && s[i])
			i++;
		if (s[i])
		{
			split[index] = malloc_word(s, c, &i);
			if (!split[index])
			{
				free_split(split, index);
				return (0);
			}
			index++;
		}
	}
	split[index] = NULL;
	return (1);
}

static char	**ft_split_a(const char *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!split)
		return (NULL);
	if (!fill_array(s, c, split))
		return (NULL);
	return (split);
}

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

	cmd = malloc(sizeof(t_command));
	cmd->args = ft_split_a((const char *)command, ' ');
	cmd->command = ft_strdup((const char *)cmd->args[0]);
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

static char	*return_last(char **fd)
{
	int	i;

	i = 0;
	while (fd[i])
		i++;
	if (i == 0)
		return (NULL);
	return (fd[i]);
}

static void	print_head_second(char **fd, char *str)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		printf("%s = %s\n", str,  fd[i]);
		i++;
	}
}

t_command_head	*return_main(t_head *head, t_main *main)
{
	t_command_head	*head_main;
	t_list			*lst_cmd;
	char			**out_fd;
	char			**in_fd;

	in_fd = return_fd(head, '<');
	out_fd = return_fd(head, '>');
	print_head_second(out_fd, "out");
	print_head_second(in_fd, "in");
	lst_cmd = NULL;
	ft_lstadd_back(&lst_cmd, ft_lstnew("\0"));
	head_main = malloc(sizeof(t_command_head));
	head_main->in_fd = return_last(in_fd);
	head_main->out_fd = return_last(out_fd);
	head_main->error = 0;
	head_main->here_doc = 0;
	head_main->out_mode = 0;
	head_main->envp = main->g_env;
	separated(head, &lst_cmd);
	head_main->head = return_command_main(lst_cmd);
	head_main->size = ft_lstsize(lst_cmd);
	return (head_main);
}
