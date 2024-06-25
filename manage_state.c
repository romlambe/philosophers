/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:10:41 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/25 15:43:36 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*create_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(data->philo[i]->thread, NULL, &state_thread_philo, data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(*data->philo[i]->thread, NULL);
		i++;
	}
	return ((void *)data);
}


void	*state_thread_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("%d\n", philo->state);
	if (philo->state == THINK)
	{
		// ph_write_state(philo);
		philo->state = EAT;
		printf("%d\n", philo->state);
	}
	// while (philo->data->nb_eat == -1 || philo->meals_eaten < philo->data->nb_eat)
	// {
		// if (philo->state == DEAD)
		// {
		// 	printf("il est mort lol\n");
		// 	return (NULL);
		// }
		// else if (philo->last_meal + philo->data->time_to_die < gettime())
		// {
		// 	philo->state = DEAD;
		// 	ph_write_state(philo);
		// 	return (NULL);
		// }
		// if (philo->state == THINK)
		// {
		// 	// ph_write_state(philo);
		// 	philo->state = EAT;
		// 	printf("%d\n", philo->state);
		// }
		// else if (philo->state == EAT)
		// {
		// 	philo = ph_eat();
		// 	//ft qui lui permet de voir s'il peut manger ou non (2 forks)
		// }
		// else if (philo->state == SLEEP)
		// {
		// 	philo = ph_sleep();
		// 	//ft qui lui permet de sleep;
		// }
	// }
	return (NULL);
}

void	ph_write_state(t_philo *philo)
{
	// size_t	time;

	pthread_mutex_lock(&philo->data->pen);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->pen);
		return ;
	}
	// time = gettime() - philo->data->start_time;
	if (philo->state == DEAD)
	{
		printf("le philo %d est dead à %zu\n",philo->id ,gettime());
		philo->data->dead = 1;
	}
	else if (philo->state == THINK)
		printf("le philo %d que il gamberge\n", philo->id);
	else if (philo->state == EAT)
		printf("le philo %d que il se regale MIAMMM\n",philo->id);
	else if (philo->state == SLEEP)
		printf ("le philo %d QUE il dort ce fou\n", philo->id);
	pthread_mutex_unlock(&philo->data->pen);
}

// t_philo	*ph_eat()
// {

// }

// t_philo	*ph_sleep()
// {

// }
