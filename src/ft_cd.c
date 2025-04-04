/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:25:14 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/04 13:29:41 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(char **cmd)
{
    char *path;
    char *home;
    unsigned char exit_code;

    if (cmd[1] && cmd[2])
        return(ft_printf(2, "cd: too many arguments\n"), 1);
    if (!cmd[1])
    {
        home = getenv("HOME");
        if (!home)
            return(ft_putstr_fd("cd: HOME undefined\n", 2), 1);
        path = home;
    }
    else
    {
        path = cmd[1];
        if (path[0] == '~')
        {
            home = getenv("HOME");
            if (!home)
                return(ft_putstr_fd("cd: HOME undefined\n", 2), 1);
            path = ft_strjoin(home, path + 1);
        }
    }
    if (chdir(path) == -1)
    {
        ft_printf(2, "cd: %s: %s\n", path, strerror(errno));
        exit_code = 1;
    }
    else
        exit_code = 0;

    return (exit_code);
}