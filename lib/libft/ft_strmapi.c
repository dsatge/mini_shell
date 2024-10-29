/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:57:36 by dsatge            #+#    #+#             */
/*   Updated: 2023/12/08 15:17:14 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	str = ft_strdup(s);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, str[i]);
		i++;
	}
	return (str);
}
/*
char	totoupper(unsigned int i, char c)
{
	(void)i;	
	if (c >= 'a' && c <= 'z')
		c = (c - 32);
	return (c);
}

int	main(void)
{
	
	printf("*ft_strmapi return %s\n", ft_strmapi("hello", totoupper));
}*/
