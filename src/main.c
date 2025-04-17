/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:57 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/17 14:41:49 by enschnei         ###   ########.fr       */
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
		free_list(token_list);
		free_env(&mini_struct->env);
		free(mini_struct);
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

void	ft_handle_input_line(char *buffer, t_minish *mini_struct)
{
	t_token	*head;
	t_list	*cmds;
	t_list	*curr_cmd;

	head = ft_split_word(buffer, mini_struct);
	if (ft_checktype_order(head) == 0)
	{
		cmds = malloc(sizeof(t_list));
		if (!cmds)
			return ;
		cmds_list(head, cmds);
		curr_cmd = cmds;
		ft_exec(curr_cmd, &mini_struct->env, mini_struct);
		free_list(head);
		free_cmds(cmds);
	}
	else
		free_list(head);
	free(buffer);
}

static void	process_input(char *buffer, t_token **head, t_minish *mini_struct)
{
	t_list	*curr_cmd;

	if (error_special(buffer) == 1)
		return ;
	*head = ft_split_word(buffer, mini_struct);
	if (ft_checktype_order(*head) == 0)
	{
		mini_struct->cmds = malloc(sizeof(t_list));
		if (!mini_struct->cmds)
			return ;
		cmds_list(*head, mini_struct->cmds);
		curr_cmd = mini_struct->cmds;
		ft_exec(mini_struct->cmds, &mini_struct->env, mini_struct);
		free_list(*head);
		free_cmds(curr_cmd);
	}
	else
	{
		free_list(*head);
	}
	*head = NULL;
	free(buffer);
}

static void	ft_prompt(t_token *head, t_minish *mini_struct)
{
	char	*buffer;
	int		buf_value;

	while (1)
	{
		signal_handle();
		if (isatty(STDIN_FILENO) == 0)
			buffer = get_next_line(STDIN_FILENO);
		else
			buffer = readline(PROMPT);
		if (!buffer)
			break ;
		buf_value = ft_buffer(buffer, head, mini_struct);
		if (buf_value == -1)
			return ;
		if (buf_value == 0)
			process_input(buffer, &head, mini_struct);
	}
}

int	main(int ac, char **av, char **env)
{
	t_minish	*mini_struct;
	t_token		*head;
	t_list		*cmds;

	(void)ac;
	(void)av;
	head = NULL;
	cmds = NULL;
	rl_outstream = stderr;
	mini_struct = ft_calloc(sizeof(t_minish), 1);
	if (!mini_struct)
		return (ft_putstr_fd("Error malloc minish in main\n", 2), -1);
	ft_init_env(env, &mini_struct->env);
	ft_prompt(head, mini_struct);
	free_env(&mini_struct->env);
	free_list(head);
	free(mini_struct);
	return (0);
}
