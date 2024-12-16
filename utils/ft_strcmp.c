/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-goff <tle-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 09:59:24 by tle-goff          #+#    #+#             */
/*   Updated: 2024/12/12 15:44:47 by tle-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*src;
	const unsigned char	*dest;

	src = (const unsigned char *) s2;
	dest = (const unsigned char *) s1;
	while (*src || *dest)
	{
		if (*src != *dest || *src == '\0' || *dest == '\0')
			return (*dest - *src);
		src++;
		dest++;
	}
	return (0);
}
