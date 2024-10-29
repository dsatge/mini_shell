/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:30:38 by dsatge            #+#    #+#             */
/*   Updated: 2023/11/16 10:35:44 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*str;
	char	*insert;
	int		i;
	int		j;

	str = dest;
	if (!dest && !src)
		return (dest);
	insert = (char *)src;
	i = 0;
	j = 0;
	while (n > 0)
	{
		str[i] = insert[j];
		j++;
		i++;
		n--;
	}
	return (str);
}
/*
int	main(void)
{
	char	dest[15] = "Enzo est la";
	char	dest1[15] = "Enzo est la";
	char	src[7] = "bg";
	size_t	n;

	n = 3;
	memcpy(dest + 9, src, n);
	printf("memcpy returns %s\n", dest);
	ft_memcpy(dest1 + 9, src, n);
	printf("ft_memcpy returns %s \n", dest1);
}*/
