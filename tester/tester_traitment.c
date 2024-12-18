/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_traitment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:55:25 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/18 17:36:45 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	main_tester_traitment(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (ft_strcmp((const char *)"quote", argv[i + 1]) == 0)
			tester_quote();
		if (ft_strcmp((const char *)"block", argv[i + 1]) == 0)
			tester_block();
		i++;
	}
}
