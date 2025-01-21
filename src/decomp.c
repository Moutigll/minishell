/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decomp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:43:51 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/21 18:00:17 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_delimited(const char *s, int index, int i)
{
	int	parentheses;
	int	braces;
	int	brackets;

	parentheses = 0;
	braces = 0;
	brackets = 0;
	i = 0;
	while (i < index)
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
		i++;
	}
	return (parentheses > 0 || braces > 0 || brackets > 0);
}

static int	count_words(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && !is_delimited(s, i, 0) && s[i])
			i++;
		if (s[i])
		{
			count++;
			while ((s[i] != c || is_delimited(s, i, 0)) && s[i])
				i++;
		}
	}
	return (count);
}

static char	*malloc_word(const char *s, char c, int *start)
{
	int		len;
	char	*word;
	int		i;

	i = 0;
	len = 0;
	while (s[*start + len] && (s[*start + len] != c
			|| is_delimited(s, *start + len, 0)))
		len++;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	word[len] = '\0';
	while (i < len)
	{
		word[i] = s[*start + i];
		i++;
	}
	*start += len;
	return (word);
}

static void	free_split(char **split, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	fill_array(const char *s, char c, char **split)
{
	int	index;
	int	i;

	i = 0;
	index = 0;
	while (s[i])
	{
		while (s[i] == c && !is_delimited(s, i, 0) && s[i])
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
	char	*tmp;

	lst = *lst_cmd;
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	if (n == 1 && j != 0)
	{
		tmp = lst->content;
		lst->content = ft_strjoin((const char *)tmp, " ");
		if ((int)ft_strlen(tmp) > 0)
			free(tmp);
	}
	tmp = lst->content;
	lst->content = ft_strjoin((const char *)tmp, command);
	if ((int)ft_strlen(tmp) > 0)
		free(tmp);
	free(command);
}

static void	return_command_part1(t_node *node, int *i, int *skip)
{
	while (node->content[*i])
	{
		if ((node->content[*i] == '|' || node->content[*i] == '<'
				|| node->content[*i] == '>') && node->type == 2)
			break ;
		*skip = 1;
		(*i)++;
	}
}

static void	return_command(t_node *node, int *k, t_list **lst_cmd, int j)
{
	char	*result;
	int		tmp;
	int		i;
	int		skip;

	i = 0;
	skip = 0;
	return_command_part1(node, &i, &skip);
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
	else
		free(result);
	if (node->content[i] == '|' && node->type == 2)
		ft_lstadd_back(lst_cmd, ft_lstnew("\0"));
}

static int	separated_part1(int *i, int *j, t_node *node, t_list **lst)
{
	if (*i == -1)
	{
		*lst = (*lst)->next;
		*i = 0;
		j++;
		return (1);
	}
	*i = 0;
	if ((node->content[0] == '>' || node->content[0] == '<') && node->type == 2)
	{
		*lst = (*lst)->next;
		j++;
		*i = -1;
		return (1);
	}
	return (0);
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
		if (separated_part1(&i, &j, node, &lst) == 1)
			continue ;
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
	if (cmd->args[0] != NULL)
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
	t_list		*lst_main_cmd;
	t_command	*cmd;

	lst_main_cmd = NULL;
	while (lst_cmd)
	{
		cmd = return_node(&(lst_cmd->content)[return_space(lst_cmd->content)]);
		ft_lstadd_back(&lst_main_cmd, ft_lstnew(cmd));
		if (!lst_cmd->next)
			break ;
		lst_cmd = lst_cmd->next;
	}
	return (lst_main_cmd);
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

static void	test_out(char **str, int n)
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

static void	test_in(char **str)
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

static int	count_print(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			count++;
		i++;
	}
	return (count);
}

static void	set_ptr_infd(t_command_head **head_main, char **in_fd)
{
	if (in_fd[0] != NULL && count_print(in_fd[return_last(in_fd)]) > 0)
		(*head_main)->in_fd = ft_strdup(in_fd[return_last(in_fd)]);
	else
		(*head_main)->in_fd = NULL;
}

static void	set_ptr_outfd(t_command_head **head_main, char **out_fd)
{
	if (out_fd[0] != NULL && count_print(out_fd[return_last(out_fd)]) > 0)
		(*head_main)->out_fd = ft_strdup(out_fd[return_last(out_fd)]);
	else
		(*head_main)->out_fd = NULL;
}

static void	set_ptr_here_doc(t_command_head **head_main, char **here_doc)
{
	if (here_doc[0] != NULL && count_print(here_doc[return_last(here_doc)]) > 0)
		(*head_main)->here_doc = ft_strdup(here_doc[return_last(here_doc)]);
	else
		(*head_main)->here_doc = NULL;
}

static void	return_ptr(char *str, t_head *head,
	int state, t_command_head **head_main)
{
	char	*attach;
	char	**ptr;

	attach = attach_block_quote(head);
	ptr = return_fd(attach, str);
	free(attach);
	if (state == 1)
	{
		set_ptr_infd(head_main, ptr);
		test_in(ptr);
	}
	if (state == 2)
	{
		set_ptr_outfd(head_main, ptr);
		test_out(ptr, (*head_main)->out_mode);
	}
	if (state == 3)
		set_ptr_here_doc(head_main, ptr);
	if (state == 4)
	{
		(*head_main)->out_mode = 1;
		if (ptr != NULL)
			(*head_main)->out_mode = 0;
	}
	free_tab((void **)ptr);
}

void print_arg(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("Args %i = %s\n", i, str[i]);
		i++;
	}
}

// static void	ptr(t_list *lst)
// {
// 	t_command	*node;

// 	while (lst)
// 	{
// 		node = lst->content;
// 		printf("Command = %s\n", node->command);
// 		print_arg(node->args);
// 		if (!lst->next)
// 			break ;
// 		lst = lst->next;
// 	}
// }

static int check_redirec(char *attach)
{
	int	count_a;
	int	count_b;
	int	count_c;
	int	i;
	int	in_single_quotes;
	int	in_double_quotes;

	i = 0;
	count_a = 0;
	count_b = 0;
	count_c = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (attach[i])
	{
		if (attach[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		if (attach[i] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		if (in_single_quotes || in_double_quotes)
		{
			i++;
			continue ;
		}
		if (count_b > 0 && (count_a == 0 || count_c == 0))
		{
			count_a = 0;
			count_b = 0;
			count_c = 0;
		}
		if (attach[i] != ' ' && attach[i] != '<' && attach[i] != '>' && attach[i] != '|' && count_b == 0)
			count_a++;
		if (attach[i] == '<' || attach[i] == '>' || attach[i] == '|')
			count_b++;
		if (attach[i] != ' ' && attach[i] != '<' && attach[i] != '>' && attach[i] != '|' && count_b != 0)
			count_c++;
		i++;
	}
	free(attach);
	if (count_b > 0 && (count_a == 0 || count_c == 0))
		return (0);
	return (1);
}

t_command_head	*return_main(t_head *head, t_main *main)
{
	t_command_head	*head_main;
	t_list			*lst_cmd;

	head_main = malloc(sizeof(t_command_head));
	return_ptr("<", head, 1, &head_main);
	return_ptr(">", head, 2, &head_main);
	return_ptr("<<", head, 3, &head_main);
	return_ptr(">>", head, 4, &head_main);
	lst_cmd = NULL;
	ft_lstadd_back(&lst_cmd, ft_lstnew("\0"));
	head_main->list_head = head;
	head_main->main = main;
	head_main->envp = main->g_env;
	separated(head, &lst_cmd);
	head_main->head = return_command_main(lst_cmd);
	head_main->size = ft_lstsize(lst_cmd);
	if (check_redirec(attach_block_quote(head)) == 0)
		return (NULL);
	ft_lstclear(&lst_cmd, free);
	// printf("in_fd = %s\n", head_main->in_fd);
	// printf("out_fd = %s\n", head_main->out_fd);
	// printf("here_doc = %s\n", head_main->here_doc);
	// printf("Append = %i\n", head_main->out_mode);
	// ptr(head_main->head);
	return (head_main);
}
