/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:11:40 by dsatge            #+#    #+#             */
/*   Updated: 2023/11/24 17:07:29 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	str = (char *)haystack;
	if ((*needle == '\0') || (!haystack && !needle))
		return ((char *) haystack);
	if (len == 0)
		return (NULL);
	while (str[i] && len > i)
	{
		j = 0;
		while (needle[j] && needle[j] == str[i + j])
			j++;
		if (j == ft_strlen(needle) && i + j <= len)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	haystack[] = "not the empty string";
//	char	needle[] = '\0';
	size_t		len;

	len = 3;
//	printf("strnstr returns %s\n", strnstr(haystack, needle, len));
	printf("ft_strnstr returns %s\n", ft_strnstr(haystack, NULL, len));
	return (0); 
}*/