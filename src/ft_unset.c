/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:23:37 by baiannon          #+#    #+#             */
/*   Updated: 2025/02/07 15:39:54 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_node(t_env *ev, t_env *prev)
{
    t_env *target;

    target = ev;
    if (ev == prev)
    {
        ev = ev->next;
        prev = prev->next;
        free(target->value);
        free(target);
    }
    else if (ev->next->value)
    {
        ev = ev->next;
        free(target->value);
        free(target);
        prev->next = ev;
    }
    else
    {
        ev = prev;
        free(target->value);
        free(target);
    }
}

void ft_unset(char **cmd, t_env *ev)
{
    size_t i;
    size_t y;
    t_env *tmp;
    t_env *tmp_prev;
    
    i = 1;
    while (cmd[i])
    {
        tmp = ev;
        tmp_prev = ev;
        while (ev->next->value)
        {
            y = 0;
            while (ev->value[y] == cmd[i][y])
                y++;
            if (y == ft_strlen(cmd[i]))
            {
                free_node(ev, tmp_prev);
                break;
            }
            tmp_prev = ev;
            ev = ev->next;
        }
        i++;
        // printf("VAUTERC==%s\n", ev->head->value);
        // ev = ev->head;
        ev = tmp;
        printf("CACCACACACA %s\n", tmp->value);
    }
}