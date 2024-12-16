/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:37:50 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/12 15:38:19 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	const unsigned char	*str;

	str = (const unsigned char *) s;
	while (*str != '\0' && *str != (char) c)
		str++;
	if (*str == (char) c)
		return ((char *) str);
	return (NULL);
}
