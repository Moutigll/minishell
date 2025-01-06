/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 17:16:41 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/31 15:53:44 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tester.h"

static char	*find_end(char *content)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * ((int)ft_strlen((const char *)content)));
	while (content[i] && content[i] != '|')
	{
		result[i] = content[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

void	tester_echo(t_main *main)
{
	char	*result;
	char	*line;
	t_head	*head;
	int		fd;
	int		i;

	i = 0;
	fd = open("tester/tester_echo/test.txt", O_RDONLY);
	printf("\033[1;37mTester by tle-goff | 42 Le Havre | Echo testing\033[0m\n");
	while (i >= 0)
	{
		line = get_next_line(fd);
		result = get_next_line(fd);
		if (result == NULL)
			break ;
		printf("\033[1;90m---------------------------------------------\nTest (%i) \033[0m", i);
		line = find_end(line);
		head = sanitize_input(find_end(line));
		replace_var(&head, main);
		if (ft_strcmp((const char *)echo_command(head),(const char*)find_end(result)) == 0)
			printf("\033[1;92mOK\033[0m\n");
		else
		{
			printf("\033[1;91mKO\033[0m\n");
			printf("Test Here -> %s", line);
		}
		printf("\033[1;90m---------------------------------------------\033[0m\n\n");
		free(result);
		free(line);
		i++;
	}
}
