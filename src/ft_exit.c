/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:18:32 by baiannon          #+#    #+#             */
/*   Updated: 2025/03/31 17:15:06 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exit(t_list *cmds, t_env_head *env_head)
{
    free(cmds);
    free_env(env_head);
    ft_printf("Bisous mon chou <3\n");
    exit(EXIT_SUCCESS);
}
