/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:38:17 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/15 17:13:11 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int sig)
{
	(void)sig;
	close(0);
	exit(EXIT_FAILURE);
}

static void	creat_heredoc(t_list *cmds, t_env_head *env_head)
{
	char	*buffer;
	int		fd;

	signal(SIGINT, close_fd);
	signal(SIGQUIT, SIG_IGN);
	fd = open("File_heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	while (1)
	{
		buffer = readline("heredoc> ");
		buffer = ft_expand_heredoc(buffer, env_head);
		if (!buffer || ft_strcmp(buffer, cmds->cmd->tab[1]) == 0)
		{
			free(buffer);
			break ;
		}
		ft_putstr_fd(buffer, fd);
		write(fd, "\n", 1);
		free(buffer);
	}
	close(fd);
	exit(EXIT_SUCCESS);
}

static int	exit_close(t_pipe **pipex)
{
	(*pipex)->infile_fd = open("File_heredoc", O_RDONLY);
	if ((*pipex)->infile_fd == -1)
		return (EXIT_FAILURE);
	unlink("File_heredoc");
	dup2((*pipex)->infile_fd, STDIN_FILENO);
	close((*pipex)->infile_fd);
	signal(SIGINT, sigint_handle);
	signal(SIGQUIT, SIG_IGN);
	return (EXIT_SUCCESS);
}

int	heredoc(t_pipe **pipex, t_list *cmds, t_env_head *env_head)
{
	pid_t	pid_heredoc;
	int		status;
	t_list	*list;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	list = cmds;
	while (list && list->cmd->tab != pip)
	{
		if (list->cmd->type == redir && ft_strcmp(list->cmd->tab[0], "<<") == 0)
		{
			pid_heredoc = fork();
			if (pid_heredoc == -1)
			{
				perror("Error fork heredoc");
				return (EXIT_FAILURE);
			}
			if (pid_heredoc == 0)
				creat_heredoc(list, env_head);
			waitpid(pid_heredoc, &status, 0);
		}
		list = list->next;
	}
	exit_close(pipex);
	return (EXIT_SUCCESS);
}
