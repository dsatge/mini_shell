/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:49:54 by baiannon          #+#    #+#             */
/*   Updated: 2024/12/11 19:28:19 by baiannon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int unset_env(char *ev)
{
	t_token *cmd;
	size_t len = ft_strlen(ev);
	int i = 0;
	int j;
	
	while(ev[i])
	{	
		if (ft_strcmp(ev, len) == 0 && ev[len] == '=')
		{
			free(ev);
			j = i;
			while(ev[j])
			{
				ev[j] = ev[j + 1];
				j++;
			}
		break;
		}
		i++;
	}
	return (0);
}

int ft_unset(t_token *cmd)
{
	cmd = cmd->next;
    while (cmd)
	{
        unset_env(cmd->str);
        cmd = cmd->next;
    }
	return (0);
}