/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:54:27 by dsatge            #+#    #+#             */
/*   Updated: 2023/11/27 12:21:30 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
//compile with -lbsd flag
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

// int	main(void)
// {
// 	char	dst[] = "";
// 	const char	src[] = "coucou";

// //	printf("strlcpy returns %zu\n", strlcpy(dst, src, 6));
// 	printf("ft_strlcpy returns %zu %s\n", ft_strlcpy(dst, src, 6));

// }
