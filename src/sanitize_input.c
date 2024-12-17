/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:21:47 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/18 00:17:32 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include <assert.h>

int	get_size(char *input)
{
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (input[i] != '\0')
	{
		while (input[i] != ' ' && input[i] != '\0'
			&& input[i] != '"' && input[i] != '\'')
			i++;
		if (input[i] == '"' || input[i] == '\'')
		{
			i++;
			while (input[i] != '"' && input[i] != '\'' && input[i] != '\0')
				i++;
		}
		if (input[i] == ' ')
			size++;
		i++;
	}
	return (size + 1);
}

static char	*process_quotes(char *input, int *i)
{
	int		block_len;
	char	*block;

	block_len = 0;
	block = ft_strdup("");
	if (!block)
		return (NULL);
	(*i)++;
	while (input[*i] != '"' && input[*i] != '\'' && input[*i] != '\0')
	{
		block_len++;
		(*i)++;
	}
	block = ft_strfreejoin(block, ft_substr(input, *i - block_len, block_len));
	if (input[*i] == '"' || input[*i] == '\'')
		(*i)++;
	return (block);
}

static char	*process_block(char *input, int *i)
{
	int		start;
	int		block_len;

	start = *i;
	block_len = 0;
	while (input[*i] != ' ' && input[*i] != '\0'
		&& input[*i] != '"' && input[*i] != '\'')
	{
		block_len++;
		(*i)++;
	}
	return (ft_substr(input, start, block_len));
}

char	**sanitize_input(char *input)
{
	char	**tab;
	char	*block;
	int		i;
	int		tab_n;

	tab = malloc(sizeof(char *) * (get_size(input) + 1));
	i = 0;
	tab_n = 0;
	block = ft_strdup(" ");
	while (input[i])
	{
		block = ft_strfreejoin(block, process_block(input, &i));
		if (input[i] == '"' || input[i] == '\'')
			block = ft_strfreejoin(block, process_quotes(input, &i));
		if (input[i] == ' ' || input[i] == '\0')
		{
			tab[tab_n] = block;
			tab_n++;
			if (input[i] == '\0')
				break ;
			block = ft_strdup(" ");
			i++;
		}
	}
	return ((tab[tab_n] = NULL), tab);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	char	**tab;
// 	int		len;
// 	int		i;
// 	int		j;

// 	fd = open("test.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	j = 0;
// 	while (line)
// 	{
// 		len = ft_strlen(line);
// 		if (len > 0 && line[len - 1] == '\n')
// 			line[len - 1] = '\0';
// 		tab = sanitize_input(line);
// 		char *old = line;
// 		char *str = ft_itoa(get_size(line));
// 		i = 0;
// 		while (tab[i])
// 		{
// 			str = ft_addchar(str, '[');
// 			str = ft_strfreejoin(str, tab[i]);
// 			str = ft_addchar(str, ']');
// 			i++;
// 		}
// 		str = ft_addchar(str, '\n');
// 		free(tab);
// 		line = get_next_line(fd);
// 		if (ft_strcmp(str, line) == 0)
// 		{
// 			ft_printf("\033[32mTest %d OK\033[0m\n", j);
// 			ft_printf("Input   : %s\n", old);
// 			ft_printf("Expected: %s", line);
// 			ft_printf("Got     : %s", str);
// 		}
// 		else
// 		{
// 			ft_printf("\033[31mTest %d KO\033[0m\n", j);
// 			ft_printf("Input   : %s\n", old);
// 			ft_printf("Expected: %s", line);
// 			ft_printf("Got     : %s", str);
// 			ft_printf("Diff	: %d\n", ft_strcmp(str, line));
// 		}
// 		free(str);
// 		free(line);
// 		free(old);
// 		line = get_next_line(fd);
// 		j++;
// 	}
// 	return (0);
// }
