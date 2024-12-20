/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:54:41 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/20 18:15:49 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../include/minishell.h"

// TESTER GLOBAL
void	tester_manager(char **env, t_main *main);
void	tester_quote(void);
void	tester_block(void);
void	tester_checkequal(void);
void	tester_cmd(char **env);
void	tester_echo(t_main *main);
