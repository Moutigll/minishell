/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:55:25 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/19 21:22:10 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.h"

void	tester_manager(char **env)
{
	(void)env;
	tester_quote();
	tester_block();
	tester_checkequal();
	tester_cmd(env);
}
