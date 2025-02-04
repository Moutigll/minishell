/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:47:01 by tle-goff          #+#    #+#             */
/*   Updated: 2025/02/04 13:42:20 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	check_redirect_n_part2(int *redirect, int count)
{
	*redirect = 0;
	if (count > 0)
		*redirect = 1;
}

static int	check_redirect_n(char *str, char c, char vs, int *redirect)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (str[i] == '\0' && *redirect == 1)
		return (1);
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')' || str[i] == '[' || str[i] == ']')
			return (printf("Error Parentheses/Brackets not supported\n"), 1);
		else if (str[i] == c && count > 1)
			return (printf("1 Parse error near `%c'\n", c), 1);
		else if (str[i] == c && count <= 1)
			count++;
		else if (str[i] == vs && count > 0)
			return (printf("2 Parse error near `%c%c'\n", c, vs), 1);
		else if (str[i] == '|' && count > 0)
			return (printf("3 Parse error near `%c'\n", c), 1);
		else
			count = 0;
		i++;
	}
	check_redirect_n_part2(redirect, count);
	return (0);
}

static int	change_redirect(int *state, char *str)
{
	int	i;
	int	j;

	j = 0;
	while (str[j] && str[j] != '>' && str[j] != '<'
		&& str[j] != ' ' && str[j] != '\t')
		j++;
	if ((str[j] == '>' || str[j] == '<') && *state == 1)
		return (1);
	i = (int)ft_strlen(str);
	if (i > 0)
		i--;
	while (i >= 0 && str[i])
	{
		if (str[i] != '>' && str[i] != '<' && str[i] != ' ' && str[i] != '\t')
			return (*state = 0, 0);
		if (str[i] == '>' || str[i] == '<')
			return (*state = 1, 0);
		i--;
	}
	return (0);
}

static void	declaration(int *state, int *statement,
	int *redirect_1, int *redirect_2)
{
	*state = 0;
	*statement = 0;
	*redirect_1 = 0;
	*redirect_2 = 0;
}

static int	check_redirect(t_list *lst)
{
	int		redirect_1;
	int		redirect_2;
	int		statement;
	t_node	*node;
	int		state;

	declaration(&state, &statement, &redirect_1, &redirect_2);
	while (lst)
	{
		node = lst->content;
		if (node->type == 2 && change_redirect(&state, node->content) == 1)
			return (printf("7 Parse error near `>>'\n"), 1);
		if (node->type == 2 && check_pipe(node->content, &statement))
			return (printf("6 Parse error near `||'\n"), 1);
		if (node->type == 2
			&& (check_redirect_n(node->content, '>', '<', &redirect_1) == 1
				|| check_redirect_n(node->content, '<', '>', &redirect_2) == 1))
			return (printf("11 Ambigous redirect `(null)'\n"), 1);
		if (check_brace(node->content, node->type) == 1)
			return (printf("Error bag assignment\n"), 1);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (0);
}

static t_node	*last_block(t_list *lst)
{
	t_node	*node;

	if (!lst)
		return (NULL);
	while (lst)
	{
		node = lst->content;
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (node);
}

static int	last_char(char *content, char c)
{
	int	len;

	len = (int)ft_strlen(content) - 1;
	while (len >= 0)
	{
		if ((content[len] != ' ' || content[len] != '\t')
			&& content[len] == c)
			return (1);
		else if ((content[len] != ' ' || content[len] != '\t')
			&& content[len] != c)
			return (0);
		len--;
	}
	return (0);
}

int	parse_error(t_head *head, t_main *main)
{
	t_node	*last_content;
	t_list	*lst;

	lst = head->head;
	last_content = last_block(lst);
	if (head->head != NULL
		&& ((t_node *)head->head->content)->content[0] == '|')
	{
		printf("Error: Invalid command\n");
		return (main->error = 2, 1);
	}
	if (last_content == NULL)
		return (0);
	if (last_content->type == 2 && last_char(last_content->content, '>') == 1)
		return (printf("8 Ambigous redirect `\\n'\n"), main->error = 2, 1);
	if (last_content->type == 2 && last_char(last_content->content, '<') == 1)
		return (printf("9 Ambigous redirect `\\n'\n"), main->error = 2, 1);
	if (last_content->type == 2 && last_char(last_content->content, '|') == 1)
		return (printf("4 Parse error near `%s'\n",
				last_content->content), main->error = 2, 1);
	if (check_redirect(lst) == 1)
		return (main->error = 2, 1);
	return (0);
}
