/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:48:16 by baiannon          #+#    #+#             */
/*   Updated: 2025/01/31 21:13:35 by baiannon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_init_env(char **cmd, t_env **ev)
{
    int i;
    t_env *tmp;
    
    i = 0;
    tmp = (*ev);
    while (cmd[i])
    {
        (*ev)->value = ft_strdup(cmd[i]);
        if (!cmd[i + 1])
        {
            (*ev)->next = NULL;
            break;
        }
        (*ev)->next = malloc(sizeof(t_env));
        *ev = (*ev)->next;
        i++;
    }
    *ev = tmp;
}

void ft_env(t_env **ev)
{
    t_env *tmp;

    tmp = *ev;
    while((*ev)->next)
    {
        ft_printf("%s\n", (*ev)->value);
        *ev = (*ev)->next;
    }
    *ev = tmp;
}