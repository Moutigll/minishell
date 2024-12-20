/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_checkequal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:32:29 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/19 21:16:47 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/tester.h"

void	tester_checkequal()
{
	char	*result;
	char	*line;
	char	*flag;
	int		tmp;
	int		fd;
	int		i;

	i = 0;
	fd = open("tester/tester_checkequal/test.txt", O_RDONLY);
	printf("\033[1;37mTester by tle-goff | 42 Le Havre | CheckEqual testing\033[0m\n");
	while ((line = get_next_line(fd)))
	{
		line[ft_strlen(line) - 1] = '\0';
		result = get_next_line(fd);
		flag = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("\033[1;90m---------------------------------------------\nTest (%i) \033[0m", i);
		tmp = check_equal("echo", sanitize_input(line), 0);
		if (tmp >= ft_atoi(result) && check_equal("-n", sanitize_input(line), tmp) >= ft_atoi(flag))
			printf("\033[1;92mOK\033[0m\n");
		else
		{
			printf("\033[1;91mKO\033[0m\n");
			printf("Test Here -> %s", line);
		}
		printf("\033[1;90m---------------------------------------------\033[0m\n\n");
		free(result);
		free(line);
		free(flag);
		i++;
	}
}
