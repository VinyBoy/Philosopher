/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:17:54 by marvin            #+#    #+#             */
/*   Updated: 2023/01/28 15:17:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	format(const char *str, int i, va_list arg)
{
	int	len;

	len = 0;
	if (str[i] == 's')
		len = ft_print_str(va_arg(arg, char *));
	else if (str[i] == 'c')
		len = ft_print_char(va_arg(arg, int));
	else if (str[i] == 'p')
		len = put_ptr((void *)va_arg(arg, void *));
	else if (str[i] == 'd' || str[i] == 'i')
		len = ft_print_nbr(va_arg(arg, int));
	else if (str[i] == 'u')
		len = ft_print_unsigned_nbr(va_arg(arg, unsigned int));
	else if (str[i] == 'X')
		len = ft_print_hex(va_arg(arg, unsigned int), 'X');
	else if (str[i] == 'x')
		len = ft_print_hex(va_arg(arg, unsigned int), 'x');
	else if (str[i] == '%')
		len = ft_print_char('%');
	i++;
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	int		i;
	va_list	arg;

	len = 0;
	i = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len = len + format(str, ++i, arg);
		}
		else
			len = len + write(STD_OUT, &str[i], 1);
		i++;
	}
	va_end(arg);
	return (len);
}

int main(void)
{
    int num = 42;
    char *text = "Salut";
    char c = 'a';
    ft_printf("%d\t%x\t%X\n", num, num, num);
    ft_printf("%s\t%s\t%c\t%c\t%c\n", text, text, c, 'B', ' ');
    printf("%s%d\n", "Bangbang", 43);
	ft_printf("%s vuv %d", "Bangbang", num);
	ft_printf("%c", c);


}