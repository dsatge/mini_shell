/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:53:45 by dsatge            #+#    #+#             */
/*   Updated: 2024/12/18 09:15:22 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	free_list(t_token *list)
{
	t_token *tmp;
    
	tmp = NULL;
	if (!list)
		return ;
	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp)
		{
			printf("freed : %s\n", tmp->str);
			free(tmp->str);
		}
		free(tmp);
	}
}