/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2024/10/31 17:13:31 by dsatge           ###   ########.fr       */
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

int	main(int argc, char **argv)
{

	ft_tokenise(argc, argv);
}