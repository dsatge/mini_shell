/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:09:58 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/14 19:33:58 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invert_stdin(t_list *cmds, int fd)
{
	printf("CHECK : %s, type = %i\n", cmds->cmd->tab[1], cmds->cmd->type);
	fd = open(cmds->cmd->tab[1], O_RDONLY);
	if (fd == -1)
		return (perror("open failed\n"), -1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	close(fd);
	return (0);
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
		temp = ft_strjoin(tmp->type, "=");
		if (!temp)
		{
			ft_freetab(env);
			return (NULL);
		}
		env[i] = ft_strjoin(temp, tmp->value);
		free(temp);
		if (!env[i])
		{
			ft_freetab(env);
			return (NULL);
		}
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

int	exec_single_cmd(t_list *cmds, t_pipe *pipex, t_o_cmd *o_cmd, int prev_pip,
		t_env_head *env_head)
{
	t_o_cmd	*lastCmd;

	lastCmd = o_cmd;
	while (lastCmd->next)
		lastCmd = lastCmd->next;
	if (pipe(pipex->pipe_fd) == -1)
	{
		perror("pipe");
		ft_freetab(pipex->path);
		exit(EXIT_FAILURE);
	}
	lastCmd->pid = fork();
	if (lastCmd->pid == -1)
		return (ft_putstr_fd("ERROR\n", 2), 1);
	signal_child();
	if (lastCmd->pid == 0)
	{
		last_exe(cmds, pipex, lastCmd, prev_pip, env_head);
		exit(0);
	}
	else if (lastCmd->pid > 0)
		wait_commands(o_cmd);
	return (0);
}

int	exec_multiple_cmds(t_list **cmds, t_o_cmd **o_cmd, t_pipe *pipex,
		int *prev_pip, t_env_head *env_head)
{
	t_o_cmd	*current;
	t_list	**cmds_curr;

	current = *o_cmd;
	cmds_curr = cmds;
	while (current->next)
	{
		if (pipe(pipex->pipe_fd) == -1)
			return (perror("pipe"), ft_freetab(pipex->path), exit(EXIT_FAILURE),
				0);
		current->pid = fork();
		if (current->pid == -1)
			return (ft_putstr_fd("ERROR\n", 2), 1);
		signal_child();
		if (current->pid == 0)
		{
			first_exe(*cmds, pipex, current, *prev_pip, env_head);
			exit(EXIT_SUCCESS);
		}
		close(pipex->pipe_fd[1]);
		*prev_pip = pipex->pipe_fd[0];
		next_cmdexe(cmds_curr, &current, pipex);
	}
	return (0);
}
