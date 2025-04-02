/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:09:15 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/02 14:14:27 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_dollar(t_env_head *env_head, 
    char *var_name)
{
    t_env *tmp;
    char *env_name;
    
    if (ft_strcmp(var_name, "?") == 0) // Gestion de $?
        return (ft_itoa(g_error_code));
    tmp = env_head->head;
    while (tmp)
    {
        env_name = get_type_env(tmp->type); // Récupère le nom propre de la variable
        if (ft_strcmp(env_name, var_name) == 0)
        {
            free(env_name);
            printf("%s\n", get_value_env(tmp->type));
            return (get_value_env(tmp->type)); // Récupère la valeur propre
        }
        free(env_name);
        tmp = tmp->next;
    }
    return (ft_strdup("")); // Si la variable n'existe pas, retourner une chaîne vide
}

//c de la merde