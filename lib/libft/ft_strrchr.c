/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:43:15 by dsatge            #+#    #+#             */
/*   Updated: 2023/12/06 17:35:26 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = (ft_strlen(s) - 1);
	if ((unsigned char)c == 0)
		return ((char *)s + i + 1);
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i--;
	}
	return (0);
}
/*
int	main(void)
{
	printf("strrchr returns %s\n", strrchr("Hello everyone!", 0));
	printf("ft_strrchr returns %s\n", ft_strrchr("Hello everyone!", 0));
}*/
