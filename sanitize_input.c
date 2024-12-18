/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:21:47 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/18 16:54:41 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"

typedef struct 	s_head
{
	t_list		*head;
	int			size;
}				t_head;

typedef struct 	s_node
{
	int			type;
	int			head;
	char		*content;
}				t_node;

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

t_head	*sanitize_input(char *input)
{
	t_head	*head;
	int		i;
	int		start;

	head = malloc(sizeof(t_head));
	if (!head)
		return (NULL);
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
		i++;
	}
	return (head);
}

int	main(void)
{
	int		fd, len, j = 0, passed = 0, total = 0;
	char	*line, *expected, *generated, *old;
	t_head	*head;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)))
	{
		total++;
		old = ft_strdup(line);
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		head = sanitize_input(line);
		generated = ft_itoa(head->size);
		for (t_list *tmp = head->head; tmp; tmp = tmp->next)
		{
			t_node *node = tmp->content;
			generated = ft_strfreejoin(generated, ft_itoa(node->type));
			generated = ft_strfreejoin(generated, ft_itoa(node->head));
			generated = ft_addchar(generated, '[');
			generated = ft_strfreejoin(generated, node->content);
			generated = ft_addchar(generated, ']');
		}
		free_list(head->head);
		free(head);
		expected = get_next_line(fd);
		if (expected && ft_strlen(expected) > 0
			&& expected[ft_strlen(expected) - 1] == '\n')
			expected[ft_strlen(expected) - 1] = '\0';
		if (ft_strcmp(generated, expected) == 0)
		{
			passed++;
			ft_printf("\033[32mTest %d OK\033[0m\n", j);
		}
		else
			ft_printf("\033[31mTest %d KO\033[0m\n", j);
		ft_printf("Input   : %s\n", old);
		ft_printf("Expected: %s\n", expected ? expected : "(null)");
		ft_printf("Got     : %s\n\n", generated);
		free(old);
		free(line);
		free(generated);
		free(expected);
		j++;
	}
	ft_printf("\033[32m%d/%d tests passed\033[0m\n", passed, total);
	close(fd);
	return (0);
}
