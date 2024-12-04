/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:36:45 by baiannon          #+#    #+#             */
/*   Updated: 2024/12/04 17:17:03 by baiannon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_flagN(char *s)
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

int ft_echo(t_token *cmd)
{
	int flag = 0;
	cmd = cmd->next;
	if (!cmd)
	{
		ft_printf("\n");
		return(0);
	}
	while (cmd->str && cmd->str[0] == '-' && check_flagN(cmd->str + 1))
	{
		flag = 1;
		cmd = cmd->next;
	}
	while (cmd)
	{
		ft_printf("%s", cmd->str);
		if (cmd->str)
			ft_printf(" ");
		cmd = cmd->next;
	}
	if (!flag)
		ft_printf("\n");
	return (0);
}
