/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:49:50 by dsatge            #+#    #+#             */
/*   Updated: 2023/12/06 15:05:06 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nlen(long int n)
{
	int	nlen;

	nlen = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		nlen++;
	}
	while (n > 0)
	{
		n = n / 10;
		nlen++;
	}
	return (nlen);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long int	nb;

	nb = n;
	i = nlen(n);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = 0;
	if (nb == 0)
		str[i] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
			str[i--] = nb % 10 + '0';
			nb = nb / 10;
	}
	return (str);
}
/*
int	main(void)
{
	printf("ft_itoa returns %s", ft_itoa(-4));
}
*/