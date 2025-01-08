/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:07:29 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/08 14:04:50 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	unset_cmd(t_head *head, t_main **main)
{
	char	*result;
	int		tab;
	int		tmp;
	int		n;

	tmp = check_equal("unset", head, 0);
	n = tmp;
	tab = 0;
	if (tmp >= 0)
	{
		while (n != -1 && *main)
		{
			result = attach_block(return_head(head, tmp));
			// tab = search_env(*main, result);
			printf("%s\n", result);
		}
		return (1);
	}
	return (0);
}
