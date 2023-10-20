/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:20:08 by marvin            #+#    #+#             */
/*   Updated: 2023/01/28 15:20:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ptrbase(unsigned long num, char *base, int *len)
{
	if (num > 15)
		ptrbase((num / 16), base, len);
	*len += 1;
	return (write(1, &base[num % 16], 1));
}

int	put_ptr(void *ptr)
{
	int				len;
	unsigned long	i;

	len = 0;
	if (ptr == NULL)
	{
		len += 5;
		write(1, "(nil)", 5);
	}
	else
	{
		i = (unsigned long long) ptr;
		write(1, "0x", 2);
		len += 2;
		ptrbase(i, "0123456789abcdef", &len);
	}
	return (len);
}
