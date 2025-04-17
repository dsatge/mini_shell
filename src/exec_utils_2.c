/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:09:58 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/17 12:23:20 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fill_env(char *temp, t_env *tmp, char **env, int i)
{
	temp = ft_strjoin(tmp->type, "=");
	if (!temp)
	{
		ft_freetab(env);
		return (NULL);
	}
	env[i] = ft_strjoin(temp, tmp->value);
	if (!env[i])
	{
		ft_freetab(env);
		return (NULL);
	}
	return (temp);
}

char	**buildtab(t_env_head *env_head)
{
	t_env	*tmp;
	int		i;
	char	**env;
	char	*temp;

	i = 0;
	tmp = env_head->head;
	env = malloc(sizeof(char *) * (env_head->size + 1));
	if (!env)
		return (NULL);
	while (tmp)
	{
		temp = fill_env(temp, tmp, env, i);
		if (temp == NULL)
			return (NULL);
		free(temp);
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

static void	wait_commands(t_o_cmd *cmd)
{
	int		status;
	t_o_cmd	*curr;

	curr = cmd;
	while (curr)
	{
		waitpid(curr->pid, &status, 0);
		if (WIFEXITED(status))
			g_error_code = WEXITSTATUS(status);
		curr = curr->next;
	}
}

int	exec_one_cmd(t_minish *minish, t_o_cmd *o_cmd, t_env_head *env_head)
{
	t_o_cmd	*lastcmd;

	if (!o_cmd)
		return (no_cmd_exe(minish->cmds, minish, env_head));
	lastcmd = o_cmd;
	while (lastcmd && lastcmd->next)
		lastcmd = lastcmd->next;
	if (pipe(minish->pipex->pipe_fd) == -1)
	{
		ft_freetab(minish->pipex->path);
		exit(EXIT_FAILURE);
	}
	lastcmd->pid = fork();
	if (lastcmd->pid == -1)
		return (ft_putstr_fd("ERROR\n", 2), 1);
	signal_child();
	if (lastcmd->pid == 0)
	{
		last_exe(minish->cmds, minish, lastcmd, env_head);
		ft_freetab(minish->pipex->env);
		exit(0);
	}
	else if (lastcmd->pid > 0)
		wait_commands(o_cmd);
	return (0);
}

int	exec_multiple_cmds(t_o_cmd **o_cmd, t_minish *minish, t_env_head *env_head)
{
	t_o_cmd	*current;
	t_list	**cmds_curr;

	current = *o_cmd;
	cmds_curr = &minish->cmds;
	while (current && current->next)
	{
		if (pipe(minish->pipex->pipe_fd) == -1)
			return (perror("pipe"), ft_freetab(minish->pipex->path),
				exit(EXIT_FAILURE), 0);
		current->pid = fork();
		if (current->pid == -1)
			return (ft_putstr_fd("ERROR\n", 2), 1);
		signal_child();
		if (current->pid == 0)
		{
			firsts_exe(minish->cmds, minish, current, env_head);
			exit(EXIT_SUCCESS);
		}
		close(minish->pipex->pipe_fd[1]);
		minish->pipex->prev_pip = minish->pipex->pipe_fd[0];
		next_cmdexe(cmds_curr, &current, minish->pipex);
	}
	return (0);
}
