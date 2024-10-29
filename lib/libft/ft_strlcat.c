/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:17:51 by dsatge            #+#    #+#             */
/*   Updated: 2023/12/06 17:38:33 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
int	main(void)
{
	char	dst[] = "hello";
	const char	src[] = "everyone!";
	size_t	dstsize;

	dstsize = 38;
	printf("dst before %s \n", dst);
	size_t i = strlcat(dst, src, dstsize);
	printf("strlcat returns %zu \n", i);
	printf("dst after %s \n", dst);
//	size_t i = ft_strlcat(dst, src, dstsize);
//	printf("ft_strlcat returns %zu \n", i);
//	printf("dest after %s \n", dst);
}*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	j;
	size_t	i;

	if (!size)
		return (ft_strlen(src));
	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	i = ft_strlen(dst);
	j = 0;
	while (src[j] && i + 1 < size)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[j]));
}
