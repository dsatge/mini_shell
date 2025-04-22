/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:18:32 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/23 00:12:58 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (true);
	while (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_exit(t_minish *minish)
{
	if (minish->cmds && minish->cmds->cmd.tab && minish->cmds->cmd.tab)
	{
		if (minish->cmds->cmd.tab[0]
			&& check_number(minish->cmds->cmd.tab[1]) == false)
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			g_error_code = 2;
		}
		else if (minish->cmds->cmd.tab[1] && minish->cmds->cmd.tab[2])
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			g_error_code = 1;
			return (0);
		}
	}
	if (minish->cmds && minish->cmds->cmd.tab && minish->cmds->cmd.tab[1]
		&& g_error_code == 0)
		g_error_code = ft_atoi(minish->cmds->cmd.tab[1]);
	if (minish && minish->pipex)
	{
		close(minish->pipex->backup_stdin);
		close(minish->pipex->backup_stdout);
	}
	free_all(minish, 1);
	exit(g_error_code);
}
