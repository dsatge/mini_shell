/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:49:46 by dsatge            #+#    #+#             */
/*   Updated: 2023/12/08 15:17:56 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*mem;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((nmemb * size) < nmemb || (nmemb * size) < size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (!mem)
		return (mem);
	ft_bzero(mem, (nmemb * size));
	return (mem);
}

/*int	main(void)
{
	ft_calloc(0, 0);
//	printf("\n");
	calloc(0, 0);
}*/
