/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 10:47:08 by dsatge            #+#    #+#             */
/*   Updated: 2024/08/26 18:01:52 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*desti;
	char	*srci;

	desti = (char *)dest;
	srci = (char *)src;
	if (!src && !dest)
		return (dest);
	if (dest < src)
	{
		ft_memcpy(dest, src, n);
	}
	else
	{
		while (n--)
			desti[n] = srci[n];
	}
	return (dest);
}

// int	main(void)
// {
// 	char	dest[19] = "Hello Billy";
// 	char	src[3] = "you";
//     char    destee[19] = "Hello Billy";
// 	char    srcee[3] = "you";    
// 	memmove(dest + 6, src, 12);
// 	printf("memmove %s\n", dest);
// 	ft_memmove(destee + 6, srcee, 12);
// 	printf("ft_memmove %s\n", destee);
// }
