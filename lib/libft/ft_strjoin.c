/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:15:58 by dsatge            #+#    #+#             */
/*   Updated: 2023/12/06 17:56:27 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	i;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = malloc(sizeof(char) * (s1len + s2len) + 1);
	i = 0;
	if (!str)
		return (NULL);
	while (i < (s1len))
	{
		str[i] = *s1++;
		i++;
	}
	while (i <= (s1len + s2len))
	{
		str[i] = *s2++;
		i++;
	}
	return (str);
}
/*
2 4 6 8
int	main(void)
{
	const char	s1[] = "first";
	const char	s2[] = "deusio";

	printf("ft_strjoin returns %s", ft_strjoin(s1, s2));
}*/
