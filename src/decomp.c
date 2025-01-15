/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decomp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:43:51 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/15 12:24:22 by ele-lean         ###   ########.fr       */
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

static void	add_lst(t_list **lst_cmd, char *command, int n, int j)
{
	t_list	*lst;

	lst = *lst_cmd;
	while (lst)
	{
		if (!lst->next)
			break;
		lst = lst->next;
	}
	if (n == 1 && j != 0)
		lst->content = ft_strjoin((const char *)lst->content, " ");
	lst->content = ft_strjoin((const char *)lst->content, command);
}

static void	return_command(t_node *node, int *k, t_list **lst_cmd, int j)
{
	char	*result;
	int		tmp;
	int		i;
	int		skip;

	i = 0;
	skip = 0;
	while (node->content[i])
	{
		if ((node->content[i] == '|' || node->content[i] == '<' || node->content[i] == '>') && node->type == 2)
			break;
		skip = 1;
		i++;
	}
	tmp = i;
	result = malloc(sizeof(char) * (tmp + 1));
	i = 0;
	while (tmp--)
	{
		result[i] = node->content[i];
		i++;
	}
	result[i] = '\0';
	*k += i;
	if (skip == 1)
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
	i = 0;
	result = "\0";
	lst = head->head;
	while (lst)
	{
		node = lst->content;
		if (i == -1)
		{
			lst = lst->next;
			i = 0;
			j++;
			continue ;
		}
		i = 0;
		if (node->content[0] == '>' || node->content[0] == '<')
		{
			lst = lst->next;
			j++;
			i = -1;
			continue ;
		}
		return_command(node, &i, lst_cmd, j);
		if (!lst->next)
			break;
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

static void print_hole(char **str, char *s)
{
	int	i = 0;

	while (str[i])
	{
		printf("%s%s\n", s, str[i]);
		i++;
	}
}

static int	return_last(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i == 0)
		return (0);
	return (i - 1);
}

static void test_out(char **str, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (j < i - 1)
	{
		n = 0;
		// fake_open_outfile(str[j], n);
		j++;
	}
}

static void test_in(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (j < i - 1)
	{
		// fake_open_infile(str[j]);
		j++;
	}
}

t_command_head	*return_main(t_head *head, t_main *main)
{
	t_command_head	*head_main;
	char			**here_doc;
	char			**append;
	t_list			*lst_cmd;
	char			**out_fd;
	char			**in_fd;

	in_fd = return_fd(attach_block_quote(head), "<");
	out_fd = return_fd(attach_block_quote(head), ">");
	here_doc = return_fd(attach_block_quote(head), "<<");
	append = return_fd(attach_block_quote(head), ">>");

	print_hole(in_fd, "in = ");
	print_hole(out_fd, "out = ");
	print_hole(here_doc, "here = ");
	print_hole(append, "append = ");
	lst_cmd = NULL;
	ft_lstadd_back(&lst_cmd, ft_lstnew("\0"));
	head_main = malloc(sizeof(t_command_head));
	head_main->list_head = head;
	head_main->in_fd = in_fd[return_last(in_fd)];
	head_main->out_fd = out_fd[return_last(out_fd)];
	head_main->error = 0;
	head_main->here_doc = here_doc[return_last(here_doc)];
	head_main->out_mode = 0;
	if (append != NULL)
		head_main->out_mode = 1;
	test_in(in_fd);
	test_out(out_fd, head_main->out_mode);
	head_main->envp = main->g_env;
	separated(head, &lst_cmd);
	print_list(lst_cmd);
	head_main->head = return_command_main(lst_cmd);
	head_main->size = ft_lstsize(lst_cmd);
	return (head_main);
}
