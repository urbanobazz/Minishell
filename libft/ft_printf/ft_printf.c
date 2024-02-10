/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane < ubazzane@student.42berlin.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:08:10 by ubazzane          #+#    #+#             */
/*   Updated: 2023/12/01 12:47:55 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(const char format, va_list args);

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	len;

	if (!str)
		return (-1);
	va_start(args, str);
	len = 0;
	while (*str)
	{
		if (*str == '%')
			len += print_format(*(++str), args);
		else
			len += ft_putchar(*str);
		str++;
	}
	va_end(args);
	return (len);
}

int	print_format(const char format, va_list args)
{
	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (format == 'u')
		return (ft_putnbr(va_arg(args, unsigned int)));
	else if (format == 'X')
		return (ft_puthex(va_arg(args, unsigned int), 'X'));
	else if (format == 'x')
		return (ft_puthex(va_arg(args, unsigned int), 'x'));
	else if (format == '%')
		return (ft_putchar('%'));
	return (ft_putchar(format));
}

#include <limits.h>

int	main(void)
{
	char a = 't';
	char *ptr = &a;

	printf ("[ORIGINAL]Characters: %c %c \n", 'a', 65);
	ft_printf ("[MINE]Characters: %c %c \n", 'a', 65);
	printf("\n");

	printf ("[ORIGINAL]Decimals: %d\n", 2350);
	ft_printf ("[MINE]Decimals: %d\n", 2350);
	printf("\n");

	printf ("[ORIGINAL]Width trick: %i \n", 5);
	ft_printf ("[MINE]Width trick: %i \n", 5);
	printf("\n");

	printf("[ORIGINAL] %u\n", 2555);
	ft_printf("[MINE] %u\n", 2555);
	printf("\n");

	printf ("[ORIGINAL]%s \n", "A string");
	ft_printf ("[MINE]%s \n", "A string");
	printf("\n");

	printf("[ORIGINAL] Hex capital: %X \n", 2023);
	ft_printf("[MINE] Hex capital: %X \n", 2023);
	printf("\n");

	printf("[ORIGINAL] Hex capital (16): %X \n", 16);
	ft_printf("[MINE] Hex capital (16): %X \n", 16);
	printf("\n");

	printf("[ORIGINAL] Hex: %x \n", 2023);
	ft_printf("[MINE] Hex: %x \n", 2023);
	printf("\n");

	printf("[ORIGINAL] Pointer: %p\n", ptr);
	ft_printf("[MINE] Pointer: %p\n", ptr);
	printf("\n");

	// Character edge case
	printf("[ORIGINAL] Character: %c \n", CHAR_MAX);
	ft_printf("[MINE] Character: %c \n", CHAR_MAX);
	printf("\n");

	// Decimal edge case
	printf("[ORIGINAL] Minimum Int: %d\n", INT_MIN);
	ft_printf("[MINE] Minimum Int: %d\n", INT_MIN);
	printf("\n");

	// Width trick edge case
	printf("[ORIGINAL] Width trick: %i \n", INT_MAX);
	ft_printf("[MINE] Width trick: %i \n", INT_MAX);
	printf("\n");

	// Unsigned integer edge case
	printf("[ORIGINAL] Maximum Unsigned: %u\n", UINT_MAX);
	ft_printf("[MINE] Maximum Unsigned: %u\n", UINT_MAX);
	printf("\n");

	// String edge case
	printf("[ORIGINAL] Long String: %s \n", "This is a looooooooong string.");
	ft_printf("[MINE] Long String: %s \n", "This is a looooooooong string.");
	printf("\n");

	// Hexadecimal edge case
	printf("%i\n", printf("[ORIGINAL] Hexadecimal: %X \n", INT_MAX));
	printf("%i\n", ft_printf("[MINE] Hexadecimal: %X \n", INT_MAX));
	printf("\n");

	// Hexadecimal edge case
	printf("[ORIGINAL] Lowercase Hex: %x \n", INT_MIN);
	ft_printf("[MINE] Lowercase Hex: %x \n", INT_MIN);
	printf("\n");

	// Pointer edge case
	printf("[ORIGINAL] Null Pointer: %p\n", (void *)0);
	ft_printf("[MINE] Null Pointer: %p\n", (void *)0);
	printf("\n");

	// Printf return values test

	printf("%i\n", printf(0));
	printf("%i\n", ft_printf(0));
	printf("\n");

	return (0);
}

