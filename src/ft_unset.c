/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:23:37 by baiannon          #+#    #+#             */
/*   Updated: 2025/01/31 21:16:14 by baiannon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_node(t_env **ev, t_env *to_remove)
{
    t_env   *tmp;

    tmp = *ev;
    while (tmp)
    {
        if (tmp->next == to_remove)
        {
            tmp->next = to_remove->next;
            break;
        }
        tmp = tmp->next;
    }
    if (*ev == to_remove)
        *ev = (*ev)->next;
    free(to_remove->value);
    free(to_remove);
}

void ft_unset(char **cmd, t_env **ev)
{
    size_t i;
    t_env *tmp;
    
    i = 1;

    while (cmd[i])
    {
        tmp = *ev;
        while (tmp)
        {
            if (ft_strncmp(tmp->value, cmd[i], (ft_strchr(tmp->value, '=') - tmp->value)) == 0)
            {
                free_node(ev, tmp);
                break;
            }
            tmp = tmp->next;
        }
        i++;
        // printf("VAUTERC==%s\n", ev->head->value);
        // ev = ev->head;
        // GJS_DEBUG_TOPICS
    }
}