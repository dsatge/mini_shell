/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2024/10/30 14:17:53 by dsatge           ###   ########.fr       */
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
void	ft_print_list(s_token *list)
{
	int i;
	
	i = 0;
	while (list != NULL)
	{
		ft_printf("list[%i] = %s type = %d\n", i, list->str, list->type);
		i++;
		list = list->next;
	}
	return ;
}



void	ft_token_type(char *node_content, s_token token)
{
	int i;

	i = 0;
	if (node_content[0] == '|')
	{
		token.type.pip = 1;
		return (pip = 1);
	}
	else
		return (word);
}

void add_node(s_token *element, char *node_content, s_token token)
{
	element->next = malloc(sizeof(s_token));
	if (element->next == NULL)
		return (ft_putstr_fd("Error malloc add_node", 2));
	element->next->str = ft_strdup(node_content);
	element->type = ft_token_type(node_content, token);
	element->next->next = NULL;
	return ;
}

void	ft_tokenise(int argc, char **argv)
{
	s_token *element;
	s_token *head;
	int	i;

	i = 0;
	element = malloc(sizeof(s_token));
	if (element == NULL)
		return(ft_putstr_fd("Error malloc ft_tokenise", 2));
	element->type = ft_token_type(argv[i], &token);
	element->str = ft_strdup(argv[i]);
	element->next = NULL;
	i++;
	head = element;
	while (i < argc)
	{
		if(element->next != NULL)
			element = element->next;
		add_node(element, argv[i]);
		i++;
	}
	ft_print_list(head);
}

int	main(int argc, char **argv)
{

	ft_tokenise(argc, argv);
}