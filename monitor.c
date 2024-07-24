/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:41:37 by romlambe          #+#    #+#             */
/*   Updated: 2024/07/24 00:00:54 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_if_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].num_of_philos)
	{
		if (philo_dead(&philo[i], philo[i].time_to_die))
		{
			print_message("died", &philo[i], philo[i].id);
			pthread_mutex_lock(philo[0].dead_lock);
			*philo->dead = 1;
			pthread_mutex_unlock(philo[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_nb_eat(t_philo *philo)
{
	int	i;
	int	full_eat;

	i = 0;
	full_eat = 0;
	if (philo[0].num_time_to_eat == -1)
		return (0);
	while (i < philo[0].num_of_philos)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].meals_eaten >= philo[i].num_time_to_eat)
			full_eat++;
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	if (full_eat == philo[0].num_of_philos)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *pointeur)
{
	t_philo	*philo;

	philo = (t_philo *)pointeur;
	while (1)
		if (check_if_dead(philo) == 1 || check_nb_eat(philo) == 1)
			break ;
	return (NULL);
}
