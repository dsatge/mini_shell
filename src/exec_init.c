/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:51:54 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/03 15:56:51 by dsatge           ###   ########.fr       */
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

t_o_cmd	*ft_only_cmd(t_list *cmds)
{
	t_list	*list;
	t_o_cmd	*head;
	t_o_cmd	*current;
	t_o_cmd	*new_node;
	
	int		i;
	
	list = cmds;
	head = NULL;
	current = NULL;
	i = 0;
	if (!list || !list->cmd || !list->cmd->tab[0])
		return (NULL);
	while (list)
	{
		i = 0;
		if (list->cmd->type == word)
		{
			new_node = malloc(sizeof(t_o_cmd));
			if (!new_node)
				return (NULL);
			new_node->tab = ft_calloc(sizeof(char *), ft_count_line_split(list->cmd->tab) + 1);
			if (!new_node->tab)
				return (0);
			while(list->cmd->tab[i] != 0)
			{
				new_node->tab[i] = ft_strdup(list->cmd->tab[i]);
				i++;
			}
			new_node->tab[i] = 0;
			new_node->next = NULL;
			if (head == NULL)
				head = new_node;
			else
				current->next = new_node;
			current = new_node;
		}
		list = list->next;
	}
	return (head);
}

int	next_cmdexe(t_list **cmds, t_o_cmd **o_cmd, t_pipe *pipex)
{
	if (!cmds)
		return (-1);
	pipex->outfile_fd = -1;
	pipex->nbr_cmds--;
	pipex->redir_in = 0;
	pipex->redir_out = 0;
	pipex->redir_pipe = 1;
	(*cmds)->head->cmd_nbr--;
	while (cmds && (*cmds)->cmd->type != pip)
	{
		(*cmds) = (*cmds)->next;
	}
	if (cmds && (*cmds)->cmd->type == pip)
	(*cmds) = (*cmds)->next;
	(*o_cmd) = (*o_cmd)->next;
	return (0);
}
