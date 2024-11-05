/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2024/11/05 19:22:53 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("tab[%i] = %s\n", i, tab[i]);
		i++;
	}
}

void	ft_print_list(struct s_token *list)
{
	int i;
	
	i = 0;
	while (list != NULL)
	{
		ft_printf("list[%i] = %s         type = %d\n", i, list->str, list->type);
		i++;
		list = list->next;
	}
	return ;
}

int ft_count_word(char *buffer)
{
	int i;
	int spacepoint;
	int word;
	int checkpoint;
	
	word = 0;
	i = 0;
	spacepoint = 0;
	checkpoint = 0;
	 
	while(buffer[i])
	{
		if(buffer[i] == '"')
		{
			
			while (i)
			{
				i++;
				if (buffer[i] == ' ' && checkpoint == 0)
				{
					spacepoint = i;
					checkpoint = 1;
				}
				if(buffer[i] == '"')
				{
					printf("inloop\n");
					word++;
					break;
				}
				else if (!buffer[i])
				{
					word++;
					i = spacepoint;
					break;
				}
			}	
		}
		checkpoint = 0;
		i++;
	}
	return (word);
}

int	main(int argc, char **argv)
{
	char *buffer;
	// char	**arguments;
	
	(void)argc;
	(void)argv;
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
	if (!buffer)
		return (ft_putstr_fd("Error: malloc fail prompt creation", 2), -1);
	while (1)
	{
		buffer = readline(">");
		if (!buffer)
			return (ft_putstr_fd("Error: malloc fail prompt creation", 2), -1);
		add_history(buffer);
		printf("word = %i\n", ft_count_word(buffer));
		// arguments = ft_split_word(buffer);
		// ft_tokenise(ft_count_line_split(arguments), arguments);
	}
}