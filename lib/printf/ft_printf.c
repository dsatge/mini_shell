/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:31:02 by dsatge            #+#    #+#             */
/*   Updated: 2024/02/19 19:32:57 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_type(char c, va_list args)
{
	int	len;

	len = 0;
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (c == 'p')
		return (ft_adress(va_arg(args, char *)));
	if (c == 'i' || c == 'd')
		return (ft_putnbr(va_arg(args, int), &len));
	if (c == 'u')
		return (ft_putunnbr(va_arg(args, unsigned int)));
	if (c == 'x' || c == 'X')
		return (ft_hexputnbr(va_arg(args, int), c));
	if (c == '%')
		return (ft_putchar('%'));
	return (1);
}

int	ft_printf(const char *c, ...)
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
			len += check_type(c[++i], args);
		else
			len += ft_putchar(c[i]);
		i++;
	}
	return (len);
}
/*
int	main(void)
{
	char	str[] =  "Deborah";
	char	name[] = "Satge";
	int	age;
	int	futur;
	int	agehex;
	
	age = 24;
	futur = 45226;
	agehex = 24 * futur;
	ft_printf("Hello my name is %s %c. I am %i. In %u years 
	|| I will be %x in hex. the adress is %p %% great.\n %%%%%%%%%%%% 
	||-> should be 6\n", str, name[0], age, futur, agehex, str);
	printf("Hello my name is %s %c. I am %i. In %u years 
	|| I will be %x in hex. the adress is %p %% great.\n %%%%%%%%%%%% 
	|| -> should be 6\n", str, name[0], age, futur, agehex, str);
	return(0);
}

int main()
{
	int nbr = 25;

	ft_printf("%d", nbr);
	printf("%d", nbr);
	return(0);
}*/
