/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:13:48 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/04 15:11:15 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(char **cmd)
{
    (void)cmd;
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("PWD Error");
        return (1);
    }
    ft_printf(1, "%s\n", cwd);
    free(cwd);
    g_error_code = 0;
    return (0);
}