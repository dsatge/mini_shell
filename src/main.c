/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2024/11/26 19:07:43 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_error_code = 0;

t_command_list	*ft_print_cmdlist(struct s_command_list *cmd_list)
{
	t_command_list	*head;
	int i;
	
	i = 0;
	head = cmd_list;
	if (!cmd_list)
		return(ft_putstr_fd("Error malloc add_node\n", 2), NULL);
	ft_printf("command list:\n");
	while (cmd_list->next_cmd != NULL)
	{
		// ft_printf("list[%i] = %s\n", i, cmd_list->element->str);
		i++;
		cmd_list = cmd_list->next_cmd;
	}
	ft_printf("list[%i] = %s\n", i, cmd_list->element->str);
	return (head);
}

int	ft_print_list(struct s_token *list)
{
	int i;

	i = 0;
	if (!list->str)
		return (-1);
	while (list)
	{
		printf("list[%i] = %s  type = %d\n", i, list->str, list->type);
		i++;
		list = list->next;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char	*buffer;
	t_minish	*mini_struct;
	t_command_list	*cmd_head;
	t_token		*head;
	
	(void)argc;
	(void)argv;
	head = NULL;
	mini_struct = malloc(sizeof(t_minish));
	if (!mini_struct)
		return (ft_putstr_fd("Error malloc minish in main\n", 2), -1);
	while (1)
	{
		signal_handle();
		buffer = readline(PROMPT);
		if (!buffer)
		{
			free_all(head, mini_struct);
			return (ft_putstr_fd("Exit with CTRL+D\n", 2), -1);
		}
		if (*buffer == '\0') // Segfault si on retourne a la ligne sur un prompt vide fixed
		{
			free(buffer);
			continue;
		}
		add_history(buffer);
		head = ft_split_word(buffer, mini_struct);
		cmd_head = ft_cmd_list(mini_struct, head);
		// ft_print_cmdlist(ft_cmd_list(mini_struct, head));
		ft_print_cmdlist(cmd_head);
		free_list(head);
		head = NULL;
		free(buffer);
	}
	free(mini_struct);		
}
