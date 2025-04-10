/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:36:45 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/10 17:30:03 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flagN(char *s)
{
	int	i;

	i = 0;
	if (!s[i])
		return (EXIT_FAILURE);
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
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	if (!cmd[i])
		return (write(1, "\n", 1), 0);
	while (cmd[i] && cmd[i][0] == '-' && check_flagN(cmd[i]))
	{
		flag = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_printf(1, "%s", cmd[i]);
		if (cmd[i + 1] != 0)
			ft_printf(1, " ");
		i++;
	}
	if (!flag)
		ft_printf(1, "\n");
	g_error_code = 0;
	return (0);
}
