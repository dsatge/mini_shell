/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:31:02 by dsatge            #+#    #+#             */
/*   Updated: 2025/04/19 14:37:00 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_type(char c, va_list args, int fd)
{
	int	len;

	len = 0;
	if (c == 'c')
		return (ft_putchar(va_arg(args, int), fd));
	if (c == 's')
		return (ft_putstr(va_arg(args, char *), fd));
	if (c == 'p')
		return (ft_adress(va_arg(args, char *), fd));
	if (c == 'i' || c == 'd')
		return (ft_putnbr(va_arg(args, int), &len, fd));
	if (c == 'u')
		return (ft_putunnbr(va_arg(args, unsigned int), fd));
	if (c == 'x' || c == 'X')
		return (ft_hexputnbr(va_arg(args, int), c, fd));
	if (c == '%')
		return (ft_putchar('%', fd));
	return (1);
}

int	ft_printf(int fd, const char *c, ...)
{
	va_list	args;
	int		i;
	int		len;

	va_start(args, c);
	i = 0;
	len = 0;
	if (!c)
		return (-1);
	while (c[i])
	{
		if (c[i] == '%')
			len += check_type(c[++i], args, fd);
		else
			len += ft_putchar(c[i], fd);
		i++;
	}
	return (len);
}
