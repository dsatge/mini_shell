/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/23 02:08:17 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_error_code = 0;

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
		free_all(mini_struct, 0);
		return (1);
	}
	add_history(buffer);
	return (0);
}

static void	handle_parsing_and_execution(t_minish *mini_struct, char *buffer)
{
	t_list	*curr_cmd;

	if (ft_split_word(buffer, mini_struct) == EXIT_FAILURE)
	{
		free(buffer);
		free_all(mini_struct, 0);
		return ;
	}
	free(buffer);
	if (ft_checktype_order(mini_struct->head_token) == 1)
	{
		free_all(mini_struct, 0);
		return ;
	}
	mini_struct->cmds = ft_calloc(sizeof(t_list), 1);
	if (!mini_struct->cmds)
		return ;
	cmds_list(mini_struct->head_token, mini_struct->cmds);
	curr_cmd = mini_struct->cmds;
	ft_exec(mini_struct->cmds, &mini_struct->env, mini_struct);
	free_all(mini_struct, 0);
}

static void	ft_isatty(char *buffer)
{
	rl_on_new_line();
	buffer = readline("");
}

static void	ft_prompt(t_minish *mini_struct)
{
	char	*buffer;
	int		buf_value;

	while (1)
	{
		signal_handle();
		if (isatty(STDIN_FILENO) == 0)
			ft_isatty(buffer);
		else
			buffer = readline(PROMPT);
		if (!buffer)
			break ;
		buf_value = ft_buffer(buffer, mini_struct->head_token, mini_struct);
		if (buf_value == -1)
			return ;
		mini_struct->pipex = ft_calloc(sizeof(t_pipe), 1);
		if (!mini_struct->pipex)
			return (ft_putstr_fd(PIPE_ERR, 2), free_all(mini_struct, 0));
		if (buf_value == 0)
			handle_parsing_and_execution(mini_struct, buffer);
		else
			free_for_lines(mini_struct);
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
	return (g_error_code);
}
