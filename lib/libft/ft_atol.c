/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:02:39 by dsatge            #+#    #+#             */
/*   Updated: 2024/03/12 11:40:17 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	long		result;
	long		sign;
	char		*str;

	str = (char *)nptr;
	result = 0;
	sign = 1;
	while (((*str >= 9) && (*str <= 13)) || (*str == 32))
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	if ((*str >= '0') && (*str <= '9'))
	{
		while ((*str >= '0') && (*str <= '9'))
		{
			result = (result * 10) + *str - '0';
			str++;
		}
		return (result * sign);
	}
	return (0);
}
/*
int	main(void)
{
	printf("atoi returns %d\n", atoi("-1    5"));
	printf("ft_atoi returns %d\n", ft_atoi("-1    5"));
}*/
