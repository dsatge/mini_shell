/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:37:49 by dsatge            #+#    #+#             */
/*   Updated: 2024/12/09 15:38:18 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command_list	*ft_print_cmdlist(struct s_command_list *cmd_list)
{
	t_command_list	*head;
	int i;
	
	i = 0;
	head = cmd_list;
	if (!cmd_list)
		return(ft_putstr_fd("Error no list in ft_print_cmdlist\n", 2), NULL);
	ft_printf("command list:\n");
	while (head != NULL)
	{
		printf("list[%i] = %s  type = %d\n", i, head->element->str, head->element->type);
		i++;
		head = head->next_cmd;
	}
	return (cmd_list);
}

t_dir_list	*ft_print_dirlist(struct s_dir_list *dir_list)
{
	t_dir_list	*head;
	int i;
	
	i = 0;
	head = dir_list;
	if (!dir_list)
		return(ft_putstr_fd("Error no list in ft_print_cmdlist\n", 2), NULL);
	ft_printf("dir list:\n");
	while (head != NULL)
	{
		printf("list[%i] = %s  type = %d\n", i, head->element->str, head->element->type);
		i++;
		head = head->next_dir;
	}
	return (dir_list);
}
