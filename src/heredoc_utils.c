/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:13:40 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/21 19:09:36 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int sig)
{
	(void)sig;
	close(0);
	exit(EXIT_FAILURE);
}

void	fd_close(int sig)
{
	(void)sig;
	close(0);
}

int	heredoc_name(char *name, t_list *cmds)
{
	free(cmds->cmd.tab[1]);
	cmds->cmd.tab[1] = ft_strdup(name);
	if (!cmds->cmd.tab[1])
		return (free(name), EXIT_FAILURE);
	free(name);
	return (EXIT_SUCCESS);
}
