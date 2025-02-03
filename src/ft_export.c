/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:48:19 by baiannon          #+#    #+#             */
/*   Updated: 2025/01/31 16:48:20 by baiannon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_export(char **cmd, t_env **ev)
{
    size_t i;
    t_env *tmp;

    i = 1;
    while (cmd[i])
    {
        tmp = *ev;
        while (tmp)
        {
            char *caca[] = {"unset", cmd[i], NULL};
            if (ft_strncmp(tmp->value, cmd[i], (ft_strchr(tmp->value, '=') - tmp->value)) == 0)
            {
                tmp = tmp->next;
                ft_unset(caca, ev);
            }
            if (tmp)
                tmp = tmp->next;
        }
        i++;
    }
}