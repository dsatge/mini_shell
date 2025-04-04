/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:18:32 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/04 13:36:12 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exit(t_list *cmds, t_env_head *env_head)
{
    free(cmds);
    free_env(env_head);
    ft_printf(2, "Bisous mon chou <3\n");
    exit(EXIT_SUCCESS);
}
