/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/20 14:22:25 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int		g_error_code = 0;

void	free_env(t_env_head *env_head)
{
	t_env	*tmp;
	t_env	*next;

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
		free_all(mini_struct, 0);
		return (ft_putstr_fd("exit\n", 2), -1);
	}
	if (*buffer == '\0')
	{
		free(buffer);
		return (1);
	}
	add_history(buffer);
	return (0);
}

static void	ft_prompt(t_minish *mini_struct)
{
	t_list	*curr_cmd;
	char 	*buffer;
	int		buf_value;

	while (1)
	{
		signal_handle();
		if (isatty(STDIN_FILENO) == 0)
		{
			rl_on_new_line();
			buffer = readline("");
		}
		else	
			buffer = readline(PROMPT);
		if (!buffer)
			break ;
		buf_value = ft_buffer(buffer, mini_struct->head_token, mini_struct);
		if (buf_value == -1)
			return ;
		mini_struct->pipex = ft_calloc(sizeof(t_pipe), 1);
		if (!mini_struct->pipex)
			return (ft_putstr_fd("Error malloc pipex in main\n", 2), free_all(mini_struct, 0));
		if (buf_value == 0)
		{
			if (error_special(buffer) == 1)
				continue ;
			if (ft_split_word(buffer, mini_struct) == EXIT_FAILURE)
			{
				free(buffer);
				free(mini_struct->element);
				free(mini_struct->pipex);
				continue ;
			}
			free(buffer);
			if (ft_checktype_order(mini_struct->head_token) == 1)
				continue ;
			else
				{
					mini_struct->cmds = malloc(sizeof(t_list));
					if (!mini_struct->cmds)
						return ;
					cmds_list(mini_struct->head_token, mini_struct->cmds);
					curr_cmd = mini_struct->cmds;
				if(ft_exec(mini_struct->cmds, &mini_struct->env, mini_struct) == 1)
					free_all(mini_struct, 0);
				}
			free_all(mini_struct, 0);
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_minish	*mini_struct;

	(void)ac;
	(void)av;
	mini_struct = NULL;
	rl_outstream = stderr;
	mini_struct = ft_calloc(sizeof(t_minish), 1);
	if (!mini_struct)
		return (ft_putstr_fd("Error malloc minish in main\n", 2), -1);
	ft_init_env(env, &mini_struct->env);
	mini_struct->head_token = NULL;
	ft_prompt(mini_struct);
	free_all(mini_struct, 1);
	return (0);
}
