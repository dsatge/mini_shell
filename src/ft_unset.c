/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:23:37 by baiannon          #+#    #+#             */
/*   Updated: 2025/03/28 13:33:31 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void free_node(t_env_head *env_head, t_env *prev)
// {
//     t_env *target;

//     target = env_head->head;
//     if (env_head->head == prev)
//     {
//         env_head->head = env_head->head->next;
//         prev = prev->next;
//         free(target->value);
//         free(target);
//     }
//     else if (env_head->head->next->value)
//     {
//         env_head->head = env_head->head->next;
//         free(target->value);
//         free(target);
//         prev->next = env_head->head;
//     }
//     else
//     {
//         env_head->head = prev;
//         free(target->value);
//         free(target);
//     }
// }

void ft_unset(char **cmd, t_env_head *env_head)
{
    (void) cmd;
    (void) env_head;
    // size_t i;
    // size_t y;
    // t_env *tmp;
    // t_env *tmp_prev;
    
    // i = 1;
    // while (cmd[i])
    // {
    //     tmp = env_head->head;
    //     tmp_prev = env_head->head;
    //     while (env_head->head->next->value)
    //     {
    //         y = 0;
    //         while (ev->value[y] == cmd[i][y])
    //             y++;
    //         if (y == ft_strlen(cmd[i]))
    //         {
    //             free_node(ev, tmp_prev);
    //             break;
    //         }
    //         tmp_prev = ev;
    //         ev = ev->next;
    //     }
    //     i++;
    //     // printf("VAUTERC==%s\n", ev->head->value);
    //     // ev = ev->head;
    //     ev = tmp;
    //     printf("CACCACACACA %s\n", tmp->value);
    // }
}