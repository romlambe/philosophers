/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:27:47 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/26 14:51:56 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	handle_error_arg(int ac, char **av)
{
	if (ac < 5 || ac > 6 || ac == 1)
		return (1);
	if (ft_isdigit(av) == 1)
		return (1);
	return (0);
}

//creer une ft pour mutex des forks
pthread_mutex_t	*init_mutex(t_data *data)
{
	int	i;
	pthread_mutex_t *mutex;

	i = 0;
	mutex = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!mutex)
		return (NULL);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	return (mutex);
}

t_data	*initialize_data(int ac, char **av)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->dead = 0;
	data->start_time = gettime();
	pthread_mutex_init(&data->pen, NULL);
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5]);
	else
		data->nb_eat = -1;
	data->fork = init_mutex(data);
	data = init_philo(data);
	if (!data)
		return (NULL);
	return (data);
}

t_data	*init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo *) * data->nb_philo);
	while (i < data->nb_philo)
	{
		data->philo[i] = malloc(sizeof(t_philo));
		if (!data->philo[i])
			return (NULL);
		data->philo[i]->id = i;
		data->philo[i]->state = THINK;
		data->philo[i]->dead = 0;
		data->philo[i]->data = data;
		data->philo[i]->meals_eaten = 0;
		data->philo[i]->thread = malloc(sizeof(pthread_t));
		data->philo[i]->last_meal = gettime();
		i++;
	}
	return (data);
}

int main(int ac, char **av)
{
	t_data *data;
	if (handle_error_arg(ac, av) == 1)
	{
		printf ("t nul bouffon\n");
		return 1;
	}
	data = initialize_data(ac, av);
	if (!data)
		return 1;
	create_thread(data);
	// printf("%d\n", data->nb_eat);
	// printf("%zu\n", data->time_to_die);
	// printf("%zu\n", data->time_to_eat);
	// printf("%zu\n", data->time_to_sleep);

	return (0);
}

