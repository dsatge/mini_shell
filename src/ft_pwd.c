/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:13:48 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/04 13:35:42 by dsatge           ###   ########.fr       */
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
    return (0);
}