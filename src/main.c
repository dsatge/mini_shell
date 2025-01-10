/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2025/01/10 19:45:36 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_error_code = 0;

int	ft_buffer(char *buffer, t_token *token_list, t_minish *mini_struct)
{
	(void)token_list;
	(void)mini_struct;
	if (!buffer)
	{
		free_list(token_list);
		free(mini_struct);
		return (ft_putstr_fd("Exit with CTRL+D\n", 2), -1);
	}
	if (*buffer == '\0') // Segfault si on retourne a la ligne sur un prompt vide fixed
	{
		free(buffer);
		return (1);
	}
	add_history(buffer);
	return (0);
}

int	main(int ac, char **av) // , char **env
{
	(void)ac;
	(void)av;
	char			*buffer;
	int				buf_value;
	t_minish		*mini_struct;
	t_token			*head;
	t_list			*cmds;
	
	head = NULL;
	cmds = NULL;
	mini_struct = malloc(sizeof(t_minish));
	if (!mini_struct)
		return (ft_putstr_fd("Error malloc minish in main\n", 2), -1);
	while (1)
	{
		signal_handle();
		buffer = readline(PROMPT);
		buf_value = ft_buffer(buffer, head, mini_struct);
		if ( buf_value == -1)
			return (-1);
		if (buf_value == 0)
		{
			head = ft_split_word(buffer, mini_struct);
			if (ft_checktype_order(head) == 0)
			{
				cmds = malloc(sizeof(t_list));
				if (!cmds)
					return (1);
				cmds_list(head, cmds);
				while (cmds)
				{
					printf("cmds = %s\n", cmds->cmd->tab[0]);
					// printf("cmds 2eme = %s\n", cmds->next->cmd->tab[0]);
					ft_builtin(cmds);
					cmds = cmds->next;
				}
				free_list(head);
			}
			else
				free_list(head);
			head = NULL;
			free(buffer);
		}
	}
	free(mini_struct);		
}
