/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2024/10/30 20:52:33 by baiannon         ###   ########.fr       */
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

int	main(int argc, char **argv)
{

	ft_tokenise(argc, argv);
}