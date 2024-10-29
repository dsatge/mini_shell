/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 09:26:16 by dsatge            #+#    #+#             */
/*   Updated: 2023/12/08 15:29:51 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*write_word(char const *s, size_t len, unsigned int start, char *str)
{
	unsigned int	i;
	size_t			slen;

	i = 0;
	slen = ft_strlen(s);
	while (i < (unsigned int)len)
	{
		if (start < slen)
		{
			str[i] = (char)s[start];
			i++;
			start++;
		}
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
		start = slen;
	if (len > (slen - start))
		len = slen - start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	write_word(s, len, start, str);
	return (str);
}
/*
//2 6 8 10
int	main(void)
{
	char const	s[] = "abcde";
	unsigned int	start;
	size_t		len;

	start = 2;
	len = 4;
	printf("ft_substr returns %s", ft_substr(s, start, len));
}*/