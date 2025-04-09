/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:33:04 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/04 13:21:57 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n, int *len, int fd)
{
	if (n == -2147483648)
		return (ft_putstr("-2147483648", fd));
	if (n < 0)
	{
		n = -n;
		*len += ft_putchar('-', fd);
	}
	if (n > 9)
	{
		ft_putnbr(n / 10, len, fd);
		ft_putnbr(n % 10, len, fd);
	}
	if (n <= 9)
		*len += ft_putchar(n + '0', fd);
	return (*len);
}
/*
int	main(void)
{
	int	n;

	n = -2148;
	ft_putnbr(n);
}*/
