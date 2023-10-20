/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:19:10 by marvin            #+#    #+#             */
/*   Updated: 2023/01/28 15:19:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_uputstr(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_unsigned_tcheck(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_unsigned_itoa(unsigned int n)
{
	char	*dest;
	int		len;

	len = ft_unsigned_tcheck(n);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	dest[len--] = '\0';
	while (n != '\0')
	{
		dest[len] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
	return (dest);
}

int	ft_print_unsigned_nbr(unsigned int n)
{
	char			*len;
	int				num;

	if (n == 0)
	{
		return (write(1, "0", 1));
	}
	else
	{
		len = ft_unsigned_itoa(n);
		num = ft_uputstr(len);
		free(len);
	}
	return (num);
}