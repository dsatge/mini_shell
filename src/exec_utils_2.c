/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:09:58 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/10 14:31:24 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	exec_single_cmd(t_list *cmds, t_pipe *pipex, t_o_cmd *o_cmd, int prev_pip, t_env_head *env_head)
{
	pid_t	pid;
	int		status;

	if (pipe(pipex->pipe_fd) == -1)
	{
		perror("pipe");
		ft_freetab(pipex->path);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd("ERROR\n", 2), 1);
	signal_child();
	if (pid == 0)
	{
		last_exe(cmds, pipex, o_cmd, prev_pip, env_head);
		exit(0);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_error_code = WEXITSTATUS(status);
	}
	return (0);
}

int	exec_multiple_cmds(t_list **cmds, t_o_cmd **o_cmd, t_pipe *pipex, int *prev_pip, t_env_head *env_head)
{
	pid_t	pid;

	while (pipex->nbr_cmds > 1)
	{
		if (pipe(pipex->pipe_fd) == -1)
		{
			perror("pipe");
			ft_freetab(pipex->path);
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
			return (ft_putstr_fd("ERROR\n", 2), 1);
		signal_child();
		if (pid == 0)
			first_exe(*cmds, pipex, *o_cmd, *prev_pip, env_head);
		close(pipex->pipe_fd[1]);
		*prev_pip = pipex->pipe_fd[0];
		next_cmdexe(cmds, o_cmd, pipex);
	}
	return (0);
}
