/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:38:17 by enschnei          #+#    #+#             */
/*   Updated: 2025/03/27 15:36:17 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int sig)
{
	(void)sig;
	close(0);
	ft_printf("\n");
	exit(EXIT_FAILURE);
}

static void creat_heredoc(t_list *cmds)
{
    char *buffer;
    int fd;

    fd = open("File_heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
    if (fd == -1)
        return ;
    while (1)
    {
        buffer = readline("heredoc>");
        if (!buffer)
        {
            ft_putstr_fd("close heredoc\n", 2);
            close(fd);
            unlink("File_heredoc");
            return ;
        }
        if (!ft_strcmp(buffer, cmds->cmd->tab[1]))
        {
            free(buffer);
            break;
        }
        ft_putstr_fd(buffer, fd);
        write(fd, "\n", 1);
        free(buffer);
    }
    close (fd);
}

int heredoc(t_list *cmds)
{
    int pid;
    int status;
    
	signal(SIGINT, SIG_IGN);
    pid = fork();
    if (pid == -1)
	{
		perror("Error fork heredoc");
		return (EXIT_FAILURE);
	}
    if (pid == 0)
    {
        signal(SIGINT, close_fd);
        creat_heredoc(cmds);
        exit(EXIT_SUCCESS);
    }
    wait(&status);
    signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handle);
    return (EXIT_SUCCESS);
}
