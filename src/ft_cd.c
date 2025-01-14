/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:25:14 by baiannon          #+#    #+#             */
/*   Updated: 2025/01/14 18:26:14 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_cd(t_token *cmd)
// {
//     char *path;
//     char *home;
// 	unsigned char exit_code;
	
// 	if (cmd->next != NULL && cmd->next->next != NULL && cmd->next->next->type == word)
// 	{
// 		ft_printf("cd: too many arguments\n");
// 		return (1);
// 	}
//     if (!cmd->next || !cmd->next->str)
//     {
//         home = getenv("HOME");
//         if (!home)
//             return(ft_putstr_fd("cd: HOME undefined\n", 2), 1);
//         path = home;
//     }
//     else
//     {
//         path = cmd->next->str;
//         if (path[0] == '~') {
//             home = getenv("HOME");
//             if (!home)
//                 return(ft_putstr_fd("cd: HOME undefined\n", 2), 1);
//             path = ft_strjoin(home, path + 1);
//         }
//     }
//     if (chdir(path) == -1)
//     {
// 		ft_printf("cd: %s: %s\n", path, strerror(errno));
// 		exit_code = 1;
// 	}
//     return (0);
// }
