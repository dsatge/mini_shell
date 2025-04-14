/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:51:54 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/14 19:07:09 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_count_cmds(t_list *cmd_list)
{
	t_list	*current;
	int		cmds;
	
	if (!cmd_list)
		return (-1);
	cmds = 0;
	current = cmd_list;
	while (current)
	{
		if (current->cmd->type == word)
			cmds++;
		current = current->next;
	}
	return (cmds);
}

void	init_pipex(t_list *cmds, t_pipe *pipex, char **env)
{
	pipex->abs_path = 0;
	pipex->backup_stdin = dup(STDIN_FILENO);
	pipex->backup_stdout = dup(STDOUT_FILENO);
	pipex->nbr_cmds = ft_count_cmds(cmds);
	pipex->redir_in = 0;
	pipex->redir_out = 0;
	pipex->redir_pipe = 0;

	(void)cmds;
	if (env[0] == NULL)
	pipex->abs_path = -1;
	else
	pipex->env = env;
}

int	next_cmdexe(t_list **cmds, t_o_cmd **o_cmd, t_pipe *pipex)
{
	if (!cmds)
		return (-1);
	pipex->nbr_cmds--;
	pipex->redir_pipe = 1;
	while (cmds && (*cmds)->cmd->type != pip)
	{
		(*cmds) = (*cmds)->next;
	}
	if (cmds && (*cmds)->cmd->type == pip)
		(*cmds) = (*cmds)->next;
	(*o_cmd) = (*o_cmd)->next;
	return (0);
}
