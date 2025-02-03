/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:21:47 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/03 14:49:26 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_block(int type, int ishead, char *content, t_head *head)
{
	t_list	*node;
	t_node	*node_content;

	node = malloc(sizeof(t_list));
	if (!node)
		return ;
	node_content = malloc(sizeof(t_node));
	if (!node_content)
	{
		free(node);
		return ;
	}
	node_content->type = type;
	node_content->head = ishead;
	node_content->content = content;
	node->content = node_content;
	node->next = NULL;
	ft_lstadd_back(&head->head, node);
	head->size++;
}

static void	process_word(int start, int *i, char *input, t_head *head)
{
	int	ishead;

	ishead = 0;
	if (start == 0 || input[start - 1] == ' ')
		ishead = 1;
	add_block(2, ishead, ft_substr(input, start, *i - start), head);
}

static void	process_quote(int *i, char *input, t_head *head)
{
	int		start;
	int		type;
	int		ishead;
	char	c;

	c = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] != '\0' && input[*i] != c)
		(*i)++;
	type = 0;
	ishead = 0;
	if (input[start - 1] == ' '
		|| ((input[start - 1] == '"' || input[start - 1] == '\'')
			&& (start < 2 || input[start - 2] == ' ')))
		ishead = 1;
	if (start > 0 && input[start - 1] == '"' && input[*i] == '"')
		type = 0;
	else if (start > 0 && input[start - 1] == '\'' && input[*i] == '\'')
		type = 1;
	add_block(type, ishead, ft_substr(input, start, *i - start), head);
}

t_head	*sanitize_input(char *input, t_main *main)
{
	t_head	*head;
	int		i;
	int		start;

	head = malloc(sizeof(t_head));
	if (!head)
		exit_on_error(main, MALLOC_ERROR);
	head->head = NULL;
	head->size = 0;
	i = 0;
	while (input[i])
	{
		start = i;
		while (input[i] != ' ' && input[i] != '"'
			&& input[i] != '\0' && input[i] != '\'')
			i++;
		if (start != i)
			process_word(start, &i, input, head);
		if (input[i] == '"' || input[i] == '\'')
			process_quote(&i, input, head);
		if (input[i])
			i++;
	}
	return (head);
}
