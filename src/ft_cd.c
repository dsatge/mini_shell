/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baiannon <baiannon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:25:14 by baiannon          #+#    #+#             */
/*   Updated: 2024/12/08 16:39:45 by baiannon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

int	ft_cd(t_token *cmd)
{
    char *path;
    char *home;

    if (!cmd->next || !cmd->next->str)
    {
        home = getenv("HOME");
        if (!home)
            return(ft_printf("cd: HOME undefined\n"), 1);
        path = home;
    }
    else
    {
        path = cmd->next->str;
        if (path[0] == '~') {
            home = getenv("HOME");
            if (!home)
                return(ft_printf("cd: HOME undefined\n"), 1);
            path = ft_strjoin(home, path + 1);
        }
    }
    if (chdir(path) == -1)
        ft_printf("cd: %s: %s\n", path, strerror(errno));
    return (0);
}