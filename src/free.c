/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 03:40:34 by baiannon          #+#    #+#             */
/*   Updated: 2024/11/29 16:58:30 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void    free_tokenList(t_token *list)
// {
//     t_token *temp;

//     while (list)
//     {
//         temp = list->next;
//         free(list->str);
//         free(list);
//         list = temp;
//     }
// }

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
		printf("free '%s'\n", tmp->str);
		free(tmp->str);
		free(tmp);
	}
}

void	free_cmd(struct s_command_list *cmd_list)
{
	t_command_list *tmp;
	
	if (!cmd_list)
		return ;
	while (cmd_list != NULL)
	{
		tmp = cmd_list;
		printf("free cmd: %p\n", cmd_list->element);
		cmd_list = cmd_list->next_cmd;
		free(tmp);
	}
	// ft_printf("list[%i] = %s\n", i, head->element->str);
}


void	free_all(t_token *list, t_minish *mini_struct)
{
    free_list(list);
	free(mini_struct);
}