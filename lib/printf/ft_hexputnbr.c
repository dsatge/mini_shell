/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexputnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:33:04 by dsatge            #+#    #+#             */
/*   Updated: 2023/12/28 18:28:12 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexputnbr(unsigned int n, char c)
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
		len += ft_hexputnbr(n / hex, c);
	len += ft_putchar(base[n % hex]);
	return (len);
}
/*
int	main(void)
{
	int	n;

	n = 165452;
	ft_hexputnbr(n, 'X');
}*/
