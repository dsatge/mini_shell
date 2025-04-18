/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:09:15 by enschnei          #+#    #+#             */
/*   Updated: 2025/04/17 12:25:01 by dsatge           ###   ########.fr       */
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

static char	*append_normal_char(char *res, char c)
{
	char	*temp;

	temp = ft_strjoin_char(res, c);
	if (!temp)
	{
		free(res);
		return (NULL);
	}
	free(res);
	return (temp);
}

static char	*process_expansion_loop(char *str, char *res, t_env_head *env_head)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			res = expand_exit_code(res, &i);
			if (!res)
				return (NULL);
			continue ;
		}
		if (str[i] == '$' && str[i + 1] && (ft_isalpha(str[i + 1]) || str[i
					+ 1] == '_'))
		{
			res = expand_env_variable(res, str, &i, env_head);
			if (!res)
				return (NULL);
			continue ;
		}
		res = append_normal_char(res, str[i++]);
		if (!res)
			return (NULL);
	}
	return (res);
}

static char	*ft_expand_env_vars(char *str, t_env_head *env_head)
{
	char	*res;

	if (!str || !env_head)
		return (NULL);
	res = ft_strdup("");
	if (!res)
		return (NULL);
	return (process_expansion_loop(str, res, env_head));
}

void	ft_expand_args(t_list *cmds, t_env_head *env_head)
{
	int		i;
	char	*expanded;

	i = 0;
	if (cmds->cmd.quote_t == single_q)
		return ;
	while (cmds->cmd.tab[i])
	{
		expanded = ft_expand_env_vars(cmds->cmd.tab[i], env_head);
		free(cmds->cmd.tab[i]);
		cmds->cmd.tab[i] = expanded;
		i++;
	}
}
