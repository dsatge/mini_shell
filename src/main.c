/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2024/11/11 03:28:05 by baiannon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[%i] = %s\n", i, tab[i]);
		i++;
	}
}

void	ft_print_list(struct s_token *list)
{
	int i;
	
	i = 0;
	while (list != NULL)
	{
		printf("list[%i] = %s         type = %d\n", i, list->str, list->type);
		i++;
		list = list->next;
	}
	return ;
}

int	main(int argc, char **argv)
{
	char	*buffer;
	char	**arguments;
	
	(void)argc;
	(void)argv;
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
	if (!buffer)
		return (ft_putstr_fd("Error: malloc fail prompt creation", 2), -1);
	while (1)
	{
		buffer = readline(">");
		if (*buffer == '\0') // Segfault si on retourne a la ligne sur un prompt vide fixed
			continue;
		printf("BUFFER = %s\n", buffer);
		if (!buffer)
			return (ft_putstr_fd("Error: malloc fail prompt creation", 2), -1);
		add_history(buffer);
		printf("word = %i\n", ft_count_word(buffer));
		arguments = ft_split_word(buffer);
		// ft_print_tab(arguments);
		ft_tokenise(ft_count_line_split(arguments), arguments);
	}
}