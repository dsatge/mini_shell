/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2025/03/26 15:49:56 by enschnei         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char			*buffer;
	int				buf_value;
	t_minish		*mini_struct;
	t_token			*head;
	t_list			*cmds;
	t_list			*curr_cmd;
	t_env			*ev;
	
	head = NULL;
	cmds = NULL;
	mini_struct = malloc(sizeof(t_minish));
	if (!mini_struct)
		return (ft_putstr_fd("Error malloc minish in main\n", 2), -1);
	ev = malloc(sizeof(t_env));
	ft_init_env(env, ev);
	while (1)
	{
		signal_handle();
		buffer = readline(PROMPT);
		buf_value = ft_buffer(buffer, head, mini_struct);
		if (buf_value == -1)
			return (-1);
		// if (ft_strcmp("exit", buffer) == 0)
		// 	exit(0);
		if (buf_value == 0)
		{
			head = ft_split_word(buffer, mini_struct);
			if (ft_checktype_order(head) == 0)
			{
				cmds = malloc(sizeof(t_list));
				if (!cmds)
					return (1);
				cmds_list(head, cmds);
				curr_cmd = cmds;
				printf("Launch of exec\n");
				ft_exec(curr_cmd, env, ev);
				free_list(head);
				free_cmds(cmds);
			}
			else
				free_list(head);
			head = NULL;
			free(buffer);
		}
	}
	free(mini_struct);		
}






// tableau de fd =
// 0 STDIN
// 1 STDOUT
// 2 STDERR
// 3 ...
// 4 ....
// ..ETC
// 1024 ...






// ls < in1


// dup2(in1, STDIN)
// close(STDIN);