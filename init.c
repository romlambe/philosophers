/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:47:38 by romlambe          #+#    #+#             */
/*   Updated: 2024/07/22 14:18:05 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_input(t_philo *philo, char **av)
{
	philo->num_of_philos = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->num_time_to_eat = ft_atoi(av[5]);
	else
		philo->num_time_to_eat = -1;
}

void	init_philo(t_philo *philo, t_data *data, pthread_mutex_t *fork,
			char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		init_input(&philo[i], av);
		philo[i].start_time = get_current_time();
		philo[i].last_meal = get_current_time();
		philo[i].write_lock = &data->write_lock;
		philo[i].dead_lock = &data->dead_lock;
		philo[i].meal_lock = &data->meal_lock;
		philo[i].dead = &data->dead_flag;
		philo[i].l_fork = &fork[i];
		if (i == 0)
			philo[i].r_fork = &fork[philo[i].num_of_philos - 1];
		else
			philo[i].r_fork = &fork[i - 1];
		i++;
	}
}

void	init_fork(pthread_mutex_t *fork, int num_philo)
{
	int	i;

	i = 0;
	while (i < num_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
}

void	init_program(t_data *data, t_philo *philo)
{
	data->dead_flag = 0;
	data->philo = philo;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
}
