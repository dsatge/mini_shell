/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:48:19 by baiannon          #+#    #+#             */
/*   Updated: 2025/03/26 16:40:00 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// static char	*get_type_env(t_token *token)
// {
// 	int		i;
// 	int		j;
// 	char	*res;

// 	i = 0;
// 	j = 0;
// 	while (token->value[i] != '=')
// 		i++;
// 	res = ft_calloc(sizeof(char), i + 1);
// 	while (token->value[i] && i > j)
// 	{
// 		res[j] = token->value[j];
// 		j++;
// 	}
// 	res[j] = '\0';
// 	return (res);
// }

// static void	get_value_env(t_env *env, t_token *token, char *type)
// {
// 	int	i;
// 	int	j;
// 	t_token *tmp;

// 	i = 0;
// 	j = 0;
// 	tmp = token;
// 	if (env->value)
// 	{
// 		free(env->value);
// 		env->value = NULL;
// 	}
// 	while (token->value[i] != '=' && token->value[i])
// 		i++;
// 	env->value = ft_calloc(sizeof(char), (ft_strlen(token->value) - i) + 1);
// 	i++;
// 	while (token->value[i])
// 	{
// 		env->value[j] = token->value[i];
// 		i++;
// 		j++;
// 	}
// 	env->value[j] = '\0';
// 	free(type);
// 	token = tmp;
// }

// static void creation(t_env *env, t_token *token, char *type)
// {
// 	int flag;

// 	flag = 0;
// 	while (env->next->type)
// 		{
// 			if (ft_strcmp(env->type, type) == 0)
// 			{
// 				get_value_env(env, token, type);
// 				flag = 1;
// 			}
// 			env = env->next;
// 		}
// 		if (ft_strcmp(env->type, type) != 0 && flag == 0)
// 		{
// 			env = env->next;
// 			env->type = ft_strdup(type);
// 			env->next = ft_calloc(sizeof(t_env), 1);
// 			get_value_env(env, token, type);
// 		}
// }

// int	ft_export(t_env *env, t_token *token)
// {
// 	t_env	*tmp;
// 	char	*type;

// 	tmp = env;
// 	token = token->next;
// 	while(token->value)
// 	{
// 		type = get_type_env(token);
// 		creation(env, token, type);
// 		env = tmp;
// 		token = token->next;
// 	}
// 	token->flag = 1;
// 	return (EXIT_SUCCESS);
// }