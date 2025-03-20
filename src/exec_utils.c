/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:35:36 by dsatge            #+#    #+#             */
/*   Updated: 2025/03/20 14:24:15 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

void	one_exe(t_list *cmds, t_pipe *pipex)
{
	/*MISSING:
	-securities
	-access for files
	-redirection when redir after cmd*/
	int i;
	char	*path_cmd;
	int fd;	

	i = 0;
	path_cmd = NULL;
	fd = 0;
	ft_redir(cmds, pipex);
	if (pipex->infile_fd != -1)
	{
		dup2(pipex->infile_fd, STDIN_FILENO);
		close(pipex->infile_fd);
	}
	if (pipex->outfile_fd != -1)
	{
		dup2(pipex->outfile_fd, STDOUT_FILENO);
		close(pipex->outfile_fd);
	}
	while (cmds && cmds->cmd->type != word)
		cmds = cmds->next;
	printf("ONE CMD\n");
	while (pipex->path[i])
	{
		free(path_cmd);
		path_cmd = ft_strjoin(pipex->path[i], cmds->cmd->tab[0]);
		if (access(path_cmd, F_OK | X_OK) == 0)
		{
			if (execve(path_cmd, cmds->cmd->tab, pipex->env) == -1)
				return (exit(127), perror("exe_cmd:"));
		}
		i++;
	}
	return (perror("127"));
}

void	first_exe(t_list *cmds, t_pipe *pipex)
{
	int i;
	char	*path_cmd;
	// int fd;	
	
	i = 0;
	path_cmd = NULL;
	// dup2(fd, STDIN_FILENO);
	ft_redir(cmds, pipex);
	if (pipex->outfile_fd == -1)
	{
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		close(pipex->pipe_fd[1]);
		close(pipex->pipe_fd[0]);
	}
	/// if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
	/// 	return ;
	/// close(pipex->pipe_fd[1]);
	/// close(pipex->pipe_fd[0]);
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
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
		return ;
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
		return ;
	close(pipex->pipe_fd[1]);
	close(pipex->pipe_fd[0]);
	ft_redir(cmds, pipex);
	if (pipex->infile_fd != -1)
	{
		printf("THERE IS A INFILE\n");
		dup2(pipex->infile_fd, STDIN_FILENO);
		close(pipex->infile_fd);
		close(pipex->infile_fd);
	}
	if (pipex->outfile_fd != -1)
	{
		printf("THERE IS A OUTFILE\n");
		dup2(pipex->outfile_fd, STDOUT_FILENO);
		close(pipex->outfile_fd);
		close(pipex->outfile_fd);
	}
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
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
		return ;
	close(pipex->pipe_fd[1]);
	close(pipex->pipe_fd[0]);
	ft_redir(cmds, pipex);
	if (pipex->infile_fd != -1)
	{
		printf("THERE IS A INFILE\n");
		dup2(pipex->infile_fd, STDIN_FILENO);
		close(pipex->infile_fd);
		close(pipex->infile_fd);
	}
	if (pipex->outfile_fd != -1)
	{
		printf("THERE IS A OUTFILE\n");
		dup2(pipex->outfile_fd, STDOUT_FILENO);
		close(pipex->outfile_fd);
		close(pipex->outfile_fd);
	}
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

int	ft_redir(t_list *cmds, t_pipe *pipex)
{
	t_list	*list;
	int		fd;

	list = cmds;
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
	if (!list)
		return (-1);
///////PBLM need to add default settings -> when there is no redirection, comes from the pipe
////// add settings for start (stdin), middle (stdout_fileno & stdin), end ;	
	while (list && list->cmd->type != pip)
	{
		if (list->cmd->type == redir && ft_strcmp(list->cmd->tab[0], "<") == 0)
		{
			fd = open(list->cmd->tab[1], O_RDONLY);
			if (fd == -1)
				return (-1);
			pipex->infile_fd = fd;
		}
		if (list->cmd->type == redir && ft_strcmp(list->cmd->tab[0], ">") == 0)
		{
			fd = open(list->cmd->tab[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (-1);
			pipex->outfile_fd = fd;
		}
		list = list->next;
	}
	return (0);
}