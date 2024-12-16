/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:35:02 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/12 12:07:58 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cd_cmd(char *command)
{
	char	*message;
	int		i;

	i = 2;
	while_space(command, &i);
	message = ft_strdup(&command[i]);
	if (chdir(message) == -1)
	{
		if (message[0] != '\0')
			printf("%s: No such file or directory\n", message);
	}
	free(message);
}
