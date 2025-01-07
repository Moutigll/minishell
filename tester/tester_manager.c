/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:55:25 by tle-goff          #+#    #+#             */
/*   Updated: 2025/01/06 13:11:15 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.h"

void	tester_manager(char **env, t_main *main)
{
	tester_quote();
	tester_block();
	tester_checkequal();
	tester_cmd(env);
	tester_echo(main);
}