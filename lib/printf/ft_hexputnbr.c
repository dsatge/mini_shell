/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexputnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:33:04 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/04 13:24:01 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexputnbr(unsigned int n, char c, int fd)
{
	long int	hex;
	int			len;
	char		*base;

	hex = 16;
	len = 0;
	if (c >= 'a' && c <= 'z')
		base = "0123456789abcdef";
	else if (c >= 'A' && c <= 'Z')
		base = "0123456789ABCDEF";
	else
		return (0);
	if (n >= hex)
		len += ft_hexputnbr(n / hex, c, fd);
	len += ft_putchar(base[n % hex], fd);
	return (len);
}
/*
int	main(void)
{
	int	n;

	n = 165452;
	ft_hexputnbr(n, 'X');
}*/
