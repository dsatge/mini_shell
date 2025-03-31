/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2025/03/31 14:25:31 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_error_code = 0;

void free_env(t_env_head *env_head)
{
	t_env *tmp;
	t_env *next;

	tmp = env_head->head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->type);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	env_head->head = NULL;
	env_head->size = 0;
}

int	ft_buffer(char *buffer, t_token *token_list, t_minish *mini_struct)
{
	(void)token_list;
	(void)mini_struct;
	if (!buffer)
	{
		free_list(token_list);
		free_env(&mini_struct->env);
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
	
	head = NULL;
	cmds = NULL;
	mini_struct = ft_calloc(sizeof(t_minish), 1);
	if (!mini_struct)
		return (ft_putstr_fd("Err    (void)env_head;or malloc minish in main\n", 2), -1);
	ft_init_env(env, &mini_struct->env);
	while (1)
	{
		signal_handle();
		buffer = readline(PROMPT);
		buf_value = ft_buffer(buffer, head, mini_struct);
		if (buf_value == -1)
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
				curr_cmd = cmds;
				// printf("Launch of exec\n");
				ft_exec(curr_cmd, &mini_struct->env);
				free_list(head);
				free_cmds(cmds);
			}
			else
				free_list(head);
			head = NULL;
			free(buffer);
		}
	}
	free_env(&mini_struct->env);
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