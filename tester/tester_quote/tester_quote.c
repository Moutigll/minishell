/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:32:35 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/30 12:51:18 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tester.h"

void	tester_quote()
{
	char	*result;
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open("tester/tester_quote/test.txt", O_RDONLY);
	printf("\033[1;37mTester by tle-goff | 42 Le Havre | Quote testing\033[0m\n");
	while (i < 21)
	{
		line = get_next_line(fd);
		result = get_next_line(fd);
		printf("\033[1;90m---------------------------------------------\nTest (%i) \033[0m", i);
		if (parsing_error(line, 1) == ft_atoi(result))
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
	close(fd);
}
