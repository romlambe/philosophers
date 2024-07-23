/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:24:41 by romlambe          #+#    #+#             */
/*   Updated: 2024/07/22 16:02:18 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_arg(char **av)
{
	if (ft_atoi(av[1]) > 200 || (ft_atoi(av[1]) <= 0)
		|| (check_arg(av[1]) == 1))
		return (printf("Error : Invalid philosophers number \n"), 1);
	else if (ft_atoi(av[2]) <= 0 || (check_arg(av[2]) == 1))
		return (printf("Error : Invalid time to die\n"), 1);
	else if (ft_atoi(av[3]) <= 0 || (check_arg(av[3]) == 1))
		return (printf("Error : Invalid time to eat\n"), 1);
	else if (ft_atoi(av[4]) <= 0 || (check_arg(av[4]) == 1))
		return (printf("Error : Invalid time to sleep\n"), 1);
	else if (av[5] && (ft_atoi(av[5]) < 0 || (check_arg(av[5]) == 1)))
		return (printf("Error : Invalid number of meals to be taken eat\n"), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data			*data;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	int				nb_philos;

	if (ac != 5 && ac != 6)
		return (printf("Error: Wrong arguments\n"), 1);
	if (check_valid_arg(av) == 1)
		return (printf("Error: Arguments must be number\n"), 1);
	data = NULL;
	philo = NULL;
	fork = NULL;
	nb_philos = ft_atoi(av[1]);
	data = malloc(sizeof(t_data));
	philo = malloc(sizeof(t_philo) * nb_philos);
	fork = malloc(sizeof(pthread_mutex_t) * nb_philos);
	init_data(data, philo);
	init_fork(fork, ft_atoi(av[1]));
	init_philo(philo, data, fork, av);
	if (philo->num_of_philos == 1)
		printf("philo 1 is thinking\nphilo 1 has taken a fork\nphilo 1 die\n");
	else
		thread_create(data, fork);
	ft_free(data, fork, philo);
	return (0);
}
