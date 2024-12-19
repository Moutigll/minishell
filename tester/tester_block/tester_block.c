/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:32:29 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/19 11:31:12 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	tester_block(void)
{
	int		fd, len, j = 0, passed = 0, total = 0;
	char	*line, *expected, *generated, *old;
	t_head	*head;

	fd = open("tester/tester_block/test_block.txt", O_RDONLY);
	printf("\033[1;37mTester by ele-lean | 42 Le Havre | Block testing\033[0m\n");
	if (fd < 0)
	{
		ft_printf("Error opening file");
		return ;
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
	return ;
}
