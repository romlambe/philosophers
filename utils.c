/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:33:09 by romlambe          #+#    #+#             */
/*   Updated: 2024/07/09 12:08:37 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] >= '0' && av[i][j] <= '9')
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		res;
	int		sign;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}

size_t	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

void	ft_usleep(size_t time)
{
	size_t	start;

	start = gettime();
	while (gettime() - start < time)
		usleep(500);
}

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		free(data->philo[i]->thread);
		free(data->philo[i]);
		i++;
	}
	free(data->fork);
	free(data->philo);
	free(data);
}
