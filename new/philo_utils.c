/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnieto-j <vnieto-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:16:58 by vnieto-j          #+#    #+#             */
/*   Updated: 2023/11/09 18:40:57 by vnieto-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_usleep(t_data *data, long ms)
{
	long	begin;

	begin = gettime();
	while (gettime() - begin < ms)
	{
		if (check_death(data))
			return (1);
		usleep(10);
	}
	return (0);
}

long	ft_atoi(const char *str)
{
	long			res;
	long			sign;
	unsigned int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	*ft_memset(void *s, int c, size_t n)
{
	char	*t;

	t = s;
	while (n--)
		*(t++) = c;
	return (s);
}

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*bloc;

	if (elementCount != 0 && elementSize > SIZE_MAX / elementCount)
		return (NULL);
	bloc = malloc(elementCount * elementSize);
	if (!bloc)
		return (NULL);
	ft_memset(bloc, 0, elementSize * elementCount);
	return (bloc);
}
