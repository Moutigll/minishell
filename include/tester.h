/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:54:41 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/19 21:32:03 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../include/minishell.h"

// TESTER GLOBAL
void	tester_manager(char **env);
void	tester_quote(void);
void	tester_block(void);
void	tester_checkequal(void);
void	tester_cmd(char **env);
