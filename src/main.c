/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2024/10/30 20:41:26 by dsatge           ###   ########.fr       */
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



void	ft_token_type(char *node_content, t_token *element)
{
	int i;

	i = 0;
	if (ft_ispipe == 0)
		element->type = pip;
	else if (ft_isredir == 0)
		element->type = redir;
	else
		element->type = word;
}

void add_node(t_token *element, char *node_content)
{
	element->next = malloc(sizeof(t_token));
	if (element->next == NULL)
		return (ft_putstr_fd("Error malloc add_node", 2));
	element->next->str = ft_strdup(node_content);
	ft_token_type(node_content, element->next);
	element->next->next = NULL;
	return ;
}

void	ft_tokenise(int argc, char **argv)
{
	t_token *element;
	t_token *head;
	int	i;

	i = 0;
	element = malloc(sizeof(t_token));
	if (element == NULL)
		return(ft_putstr_fd("Error malloc ft_tokenise", 2));
	element->str = ft_strdup(argv[i]);
	ft_token_type(argv[i], element);
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