/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2024/11/15 18:26:37 by baiannon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_error_code = 0;

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
	
	(void)argc;
	(void)argv;
	while (1)
	{
		signal_handle();
		buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
		if (!buffer)
			return (ft_putstr_fd("Error: malloc fail prompt creation", 2), -1);
		buffer = readline(PROMPT);
		if (!buffer)
		{
			// free_all(); //POUR PLUS TARD
			return (ft_putstr_fd("Exit with CTRL+D\n", 2), -1);
		}
		if (*buffer == '\0') // Segfault si on retourne a la ligne sur un prompt vide fixed
		{
			free(buffer);
			continue;
		}
		
		add_history(buffer);
		// printf("word = %i\n", ft_count_word(buffer));
		ft_split_word(buffer);
		// ft_print_tab(arguments);
		// ft_tokenise(ft_count_line_split(arguments), arguments);
		// free_all(NULL, arguments); // structure a envoyer
		free(buffer);
	}
}