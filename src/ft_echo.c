/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:36:45 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/15 18:37:33 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] != 'n')
		return (EXIT_FAILURE);
	i = 2;
	while (s[i])
	{
		if (s[i] != 'n')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_echo(char **cmd)
{
	int	new_line;
	int	i;

	new_line = 0;
	i = 1;
	if (!cmd[i])
		return (write(1, "\n", 1), 0);
	while (cmd[i] && check_flag(cmd[i]) == 0)
	{
		new_line = 1;
		i++;
	}
	while (cmd[i])
	{
		if (cmd[i][0] == '\\')
			ft_printf(1, "%s ", cmd[i++] + 1);
		ft_printf(1, "%s", cmd[i]);
		if (cmd[i + 1] != 0)
			ft_printf(1, " ");
		i++;
	}
	if (!new_line)
		ft_printf(1, "\n");
	g_error_code = 0;
	return (0);
}
