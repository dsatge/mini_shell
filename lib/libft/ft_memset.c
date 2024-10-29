/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:27:58 by dsatge            #+#    #+#             */
/*   Updated: 2023/11/13 15:29:59 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (str);
}
/*
int	main(void)
{
	char	str[10] = "Hello you";
	char	str1[10] = "Hello you";

	memset(str + 6, '*', 3 * sizeof(char));
	printf("memset returns %s \n", str);
	ft_memset(str1 + 6, '*', 3 * sizeof(char));
	printf("ft_memset returns %s \n", str1);
}*/
