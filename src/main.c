/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2024/12/09 16:08:06 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_error_code = 0;

int	ft_buffer(char *buffer, t_token *token_list, t_minish *mini_struct)
{
	if (!buffer)
	{
		free_all(token_list, mini_struct);
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

int	main(void)
{
	char			*buffer;
	int				buf_value;
	t_minish		*mini_struct;
	t_command_list	*cmd_head;
	t_dir_list		*dir_list;
	t_token			*head;
	
	head = NULL;
	cmd_head = NULL;
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
				cmd_head = ft_cmd_list(mini_struct, head);
				dir_list = ft_dir_list(mini_struct, head);
				ft_print_cmdlist(cmd_head);
				ft_print_dirlist(dir_list);
				free_list(head);
				free_cmd(cmd_head);
				free_dir(dir_list);
			}
			else
				free_list(head);
			head = NULL;
			free(buffer);
		}
	}
	free(mini_struct);		
}
