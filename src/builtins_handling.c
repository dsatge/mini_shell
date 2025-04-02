/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:23:54 by baiannon          #+#    #+#             */
/*   Updated: 2025/04/02 17:22:14 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strjoin_char(char *s, char c)
{
    int len;
    char *new_str;
    int i;

    if (!s)
        return (NULL);
    len = ft_strlen(s);
    new_str = malloc(sizeof(char) * (len + 2)); // +1 pour `c`, +1 pour `\0`
    if (!new_str)
        return (NULL);
    i = 0;
    while (i < len)
    {
        new_str[i] = s[i];
        i++;
    }
    new_str[i] = c; // Ajoute le caractère à la fin
    new_str[i + 1] = '\0'; // Termine la string
    return (new_str);
}


char *ft_get_env_value(t_env_head *env_head, char *var)
{
    t_env *tmp;

    tmp = env_head->head;
    while (tmp)
    {
        if (ft_strcmp(tmp->type, var) == 0)
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL); // Retourne NULL si la variable n'existe pas
}

char *ft_expand_env_vars(char *str, t_env_head *env_head)
{
    int i;
    int j;
    char *res;
    char *var_name;
    char *var_value;
    char *temp;

    if (!str || !env_head)
        return (NULL);
    res = ft_strdup(""); // Initialisation avec une chaîne vide
	if (!res)
		return (NULL);
    i = 0;
    while (str[i])
    {
		if (str[i] == '$' && str[i + 1])
        {
            if (str[i + 1] == '?') // Gestion spéciale pour `$?`
            {
                var_value = ft_itoa(g_error_code);
				if (!var_value)
					return (NULL);
                temp = ft_strjoin(res, var_value);
                free(res);
                free(var_value);
                res = temp;
                i += 2; // Sauter le `$?`
                continue;
            }
		}
        if (str[i] == '$' && str[i + 1] && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
        {
            j = i + 1;
            while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
                j++;
            var_name = ft_substr(str, i + 1, j - i - 1);
            var_value = ft_get_env_value(env_head, var_name);
            if (var_value)
            {
                temp = ft_strjoin(res, var_value);
                free(res);
                res = temp;
            }
            free(var_name);
            i = j;
        }
        else
        {
            temp = ft_strjoin_char(res, str[i]);
            free(res);
            res = temp;
            i++;
        }
    }
    return (res);
}
	
void ft_expand_args(t_list *cmds, t_env_head *env_head)
{
    int i;
    char *expanded;

    i = 0;
    while (cmds->cmd->tab[i])
    {
        expanded = ft_expand_env_vars(cmds->cmd->tab[i], env_head);
        free(cmds->cmd->tab[i]);
        cmds->cmd->tab[i] = expanded;
        i++;
    }
}

int	ft_builtin(t_list *cmds, t_pipe *pipex, t_env_head *env_head)
{
	(void)pipex;
	if (!cmds && !cmds->cmd && !cmds->cmd->tab)
		return (1);
	ft_expand_args(cmds, env_head);
	if (ft_strcmp(cmds->cmd->tab[0], "exit") == 0)
		return(ft_exit(cmds, env_head), 0);
	if (ft_strcmp(cmds->cmd->tab[0], "$") == 0)
		cmds->cmd->tab[0] = ft_dollar(env_head, cmds->cmd->tab[0]);
	else if (ft_strcmp(cmds->cmd->tab[0], "echo") == 0)
		return(ft_echo(cmds->cmd->tab), 0);
	else if (ft_strcmp(cmds->cmd->tab[0], "cd") == 0)
		return(ft_cd(cmds->cmd->tab), 0);
	else if (ft_strcmp(cmds->cmd->tab[0], "pwd") == 0)
		return(ft_pwd(cmds->cmd->tab), 0);
	else if (ft_strcmp(cmds->cmd->tab[0], "env") == 0)
		return(ft_env(env_head), 0);
	else if (ft_strcmp(cmds->cmd->tab[0], "unset") == 0)
		return(ft_unset(cmds->cmd->tab, env_head), 0);
	else if (ft_strcmp(cmds->cmd->tab[0], "<<") == 0)
		return(heredoc(cmds), 0); // pas la
	else if (ft_strcmp(cmds->cmd->tab[0], "export") == 0)
		return(ft_export(cmds->cmd->tab, env_head), 0);
	return (1);
}
