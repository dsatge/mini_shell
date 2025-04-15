/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:46:23 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/15 12:07:02 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_char(char *s, char c)
{
	int		len;
	char	*new_str;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	return (new_str);
}

static char	*ft_get_env_value(t_env_head *env_head, char *var)
{
	t_env	*tmp;

	tmp = env_head->head;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, var) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*ft_expand_env_vars(char *str, t_env_head *env_head)
{
	int		i;
	int		j;
	char	*res;
	char	*var_name;
	char	*var_value;
	char	*temp;

	if (!str || !env_head)
		return (NULL);
	res = ft_strdup("");
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (str[i + 1] == '?')
			{
				var_value = ft_itoa(g_error_code);
				if (!var_value)
					return (NULL);
				temp = ft_strjoin(res, var_value);
				if (!temp)
				{
					free(res);
					free(var_value);
					return (NULL);
				}
				free(res);
				free(var_value);
				res = temp;
				i += 2;
				continue ;
			}
		}
		if (str[i] == '$' && str[i + 1] && (ft_isalpha(str[i + 1]) || str[i
				+ 1] == '_'))
		{
			j = i + 1;
			while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
				j++;
			var_name = ft_substr(str, i + 1, j - i - 1);
			var_value = ft_get_env_value(env_head, var_name);
			if (var_value)
			{
				temp = ft_strjoin(res, var_value);
				if (!temp)
				{
					free(res);
					free(var_name);
					return (NULL);
				}
				free(res);
				res = temp;
			}
			free(var_name);
			i = j;
		}
		else
		{
			temp = ft_strjoin_char(res, str[i]);
			if (!temp)
			{
				free(res);
				return (NULL);
			}
			free(res);
			res = temp;
			i++;
		}
	}
	return (res);
}

char	*ft_expand_heredoc(char *buffer, t_env_head *env_head)
{
	char	*expanded;

	if (!buffer)
		return (NULL);
	expanded = ft_expand_env_vars(buffer, env_head);
	if (ft_strcmp(buffer, expanded) != 0)
	{
		free(buffer);
		return (expanded);
	}
	return (buffer);
}
