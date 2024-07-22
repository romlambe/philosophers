/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:07:41 by romlambe          #+#    #+#             */
/*   Updated: 2024/07/22 14:22:30 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*routine(void *pointeur)
{
	t_philo	*philo;

	philo = (t_philo *)pointeur;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointeur);
}

int	thread_create(t_data *data, pthread_mutex_t *fork)
{
	pthread_t	thread;
	int			i;

	if (pthread_create(&thread, NULL, &monitor, data->philo) != 0)
		ft_free(data, fork);
	i = 0;
	while (i < data->philo[0].num_of_philos)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &routine
				, &data->philo[i]) != 0)
			ft_free(data, fork);
		i++;
	}
	i = 0;
	if (pthread_join(thread, NULL) != 0)
		ft_free(data, fork);
	while (i < data->philo[0].num_of_philos)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			ft_free(data, fork);
		i++;
	}
	return (0);
}
