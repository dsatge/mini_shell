/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:38:17 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/08 17:51:44 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int sig)
{
	(void)sig;
	close(0);
	// ft_printf(2, "\n");
	exit(EXIT_FAILURE);
}

static void creat_heredoc(t_pipe **pipex, t_list *cmds)
{
    char	*buffer;
	char	*path_cmd;
	int	i;
    int fd;

	i = 0;
	path_cmd = NULL;
    (void)pipex;
    fd = open("File_heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
    if (fd == -1)
        return ;
    while (1)
    {
        buffer = readline("heredoc> ");
        if (!buffer)
        {
            ft_putstr_fd("close heredoc\n", 2);
            unlink("File_heredoc");
            return ;
        }
        if (!ft_strcmp(buffer, cmds->cmd->tab[1]))
        {
            close(fd);
            break;
        }
        ft_putstr_fd(buffer, fd);
        write(fd, "\n", 1);
        free(buffer);
    }
}

int heredoc(t_pipe **pipex, t_list *cmds)
{
    int		pid;
    int		status;
    t_list	*list;
    
	signal(SIGINT, SIG_IGN);
	list = cmds;
	while (list && list->cmd->type != pip)
    {
		if (list->cmd->type == redir && ft_strcmp(list->cmd->tab[0], "<<") == 0)
		{
			pid = fork();
		    if (pid == -1)
			{
				perror("Error fork heredoc");
				return (EXIT_FAILURE);
			}
			if (pid == 0)
			{
				signal(SIGINT, close_fd);
				creat_heredoc(pipex, list);
				exit(EXIT_SUCCESS);
			}
		}
		list = list->next;
	}
    waitpid(pid, &status, 0);
    (*pipex)->infile_fd = open("File_heredoc", O_RDONLY);
    if ((*pipex)->infile_fd == -1)
        return (EXIT_FAILURE);
    dup2((*pipex)->infile_fd, STDIN_FILENO);
    close((*pipex)->infile_fd);
	unlink("File_heredoc");
    signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handle);
    return (EXIT_SUCCESS);
}
