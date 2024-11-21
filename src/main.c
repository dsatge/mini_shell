/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2024/11/21 18:51:28 by dsatge           ###   ########.fr       */
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
	while (list)
	{
		printf("list[%i] = %s  type = %d\n", i, list->str, list->type);
		i++;
		list = list->next;
	}
	return ;
}

int	main(int argc, char **argv)
{
	char	*buffer;
	t_token	*element;
	t_token	*head;
	t_command_list	*cmd_head;
	t_command_list	*cmd;
	
	
	(void)argc;
	(void)argv;
	element = malloc(sizeof(t_token));
	if (!element)
		return (ft_putstr_fd("Error malloc ft_tokenise\n", 2), -1);
	head = element;
	while (1)
	{
		buffer = readline(">");
		if (buffer == NULL) // Segfault si on retourne a la ligne sur un prompt vide fixed
		{
			free(buffer);
			break;
		}
		if (!buffer)
			return (ft_putstr_fd("Error: malloc fail prompt creation", 2), -1);
		add_history(buffer);
		ft_split_word(buffer, &element);
		cmd = malloc(sizeof(t_command_list));
		if (!cmd)
			return (ft_putstr_fd("Error malloc cmd in main", 2), -1);
		cmd_head = cmd;
		// free(element);
		// ft_print_list(head);
		// free_all(NULL, arguments); // structure a envoyer
		free(buffer);
	}
}