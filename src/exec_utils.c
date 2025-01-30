/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:35:36 by dsatge            #+#    #+#             */
/*   Updated: 2025/01/30 16:35:43 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	one_exe(t_list *cmds, t_pipe *pipex)
{
	int i;
	char	*path_cmd;
	int fd;	

	i = 0;
	path_cmd = NULL;
	pipex->file = NULL;
	fd = 0;
	if (cmds->cmd->type == redir)
	{
		printf("HONEY I M IN\n");
		while (cmds && cmds->cmd->type == redir && cmds->cmd->type != pip)
		{
			/////// CHECCK ACCESS
			printf("CHECK : %s, type = %i\n", cmds->cmd->tab[1], cmds->cmd->type);
			fd = open(cmds->cmd->tab[1], O_RDONLY);
			if (fd == -1)
				return (perror("open failed\n"));
			if (dup2(fd, STDIN_FILENO) == -1)
				return ;
			// if (dup2(fd, STDOUT_FILENO) == -1)
			// 	return ;
			close(fd);
			cmds = cmds->next;
		}
	}
	printf("ONE\n");
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], cmds->cmd->tab[0]);
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, cmds->cmd->tab, pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	return (perror("NOPE"));
}

void	first_exe(t_list *cmds, t_pipe *pipex)
{
	int i;
	char	*path_cmd;
	// int fd;	
	
	i = 0;
	path_cmd = NULL;
	pipex->file = NULL;
	// dup2(fd, STDIN_FILENO);
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
		return ;
	close(pipex->pipe_fd[1]);
	close(pipex->pipe_fd[0]);
	// fd = open()
	// if (invert_inout(&pipex, 0, fd) == -1)
	// 	return ;
	// (void)fd;
	printf("FIRST\n");
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], cmds->cmd->tab[0]);
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, cmds->cmd->tab, pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	return (perror("NOPE"));
}

void	next_exe(t_list *cmds, t_pipe *pipex)
{
	int i;
	char	*path_cmd;
	// int fd;	

	i = 0;
	path_cmd = NULL;
	pipex->file = NULL;
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
		return ;
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
		return ;
	close(pipex->pipe_fd[1]);
	close(pipex->pipe_fd[0]);
	// fd = open()
	// if (invert_inout(&pipex, 0, fd) == -1)
	// 	return ;
	// (void)fd;
	printf("FOLLOWERS....\n");
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], cmds->cmd->tab[0]);
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, cmds->cmd->tab, pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	return (perror("NOPE"));
}

void	last_exe(t_list *cmds, t_pipe *pipex)
{
	int i;
	char	*path_cmd;
	// int fd;	

	i = 0;
	path_cmd = NULL;
	pipex->file = NULL;
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
		return ;
	close(pipex->pipe_fd[1]);
	close(pipex->pipe_fd[0]);
	// fd = open()
	// if (invert_inout(&pipex, 0, fd) == -1)
	// 	return ;
	// (void)fd;
	printf("LAST....\n");
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], cmds->cmd->tab[0]);
		if (access(path_cmd, F_OK | X_OK) == 0 && execve(path_cmd, cmds->cmd->tab, pipex->env) == -1)
			return (exit(127), perror("exe_cmd:"));
		i++;
	}
	return (perror("NOPE"));
}
