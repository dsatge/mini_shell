/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2024/11/29 18:28:24 by baiannon         ###   ########.fr       */
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
		return(ft_putstr_fd("Error no list in ft_print_cmdlist\n", 2), NULL);
	ft_printf("command list:\n");
	while (head != NULL)
	{
		printf("adress : %p list[%i] = %s  type = %d\n", head->element, i, head->element->str, head->element->type);
		i++;
		head = head->next_cmd;
	}
	return (cmd_list);
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
	cmd_head = NULL;
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
		ft_echo(head); // A RETIRER
		if (ft_checktype_order(head) == 0)
		{
			cmd_head = ft_cmd_list(mini_struct, head);
			ft_print_cmdlist(cmd_head);
			free_list(head);
			free_cmd(cmd_head);
		}
		else
			free_list(head);
		head = NULL;
		free(buffer);
	}
	free(mini_struct);		
}
