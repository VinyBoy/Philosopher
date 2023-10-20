/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:18:30 by marvin            #+#    #+#             */
/*   Updated: 2023/01/28 15:18:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_tcheck(int n)
{
	int				count;
	unsigned int	nb;

	count = 1;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	nb = n;
	while (nb > 9)
	{
		count++;
		nb = nb / 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*dest;
	int				len;
	unsigned int	nb;

	len = ft_tcheck(n);
	dest = (char *)malloc (sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	dest[len--] = '\0';
	if (n == 0)
		dest[0] = '0';
	if (n < 0)
	{
		n = n * -1;
		dest[0] = '-';
	}
	nb = n;
	while (nb > 0)
	{
		dest[len] = (nb % 10) + 48;
		nb = nb / 10;
		len--;
	}
	return (dest);
}

int	ft_print_nbr(int n)
{
	char	*len;
	int		num;

	len = ft_itoa(n);
	num = ft_putstr(len);
	free(len);
	return (num);
}
