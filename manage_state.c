/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:10:41 by romlambe          #+#    #+#             */
/*   Updated: 2024/07/11 14:51:45 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*create_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(data->philo[i]->thread, NULL, &state_thread_philo,
			(void *)data->philo[i]);
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
	while (philo->data->nb_eat == -1
		|| philo->meals_eaten < philo->data->nb_eat)
	{
		if (philo->state == DEAD)
			return (NULL);
		if (philo->last_meal + philo->data->time_to_die < gettime())
		{
			philo->state = DEAD;
			ph_write_state(philo);
			return (NULL);
		}
		if (philo->state == THINK)
		{
			ph_write_state(philo);
			philo->state = EAT;
		}
		else if (philo->state == EAT)
			philo = ph_eat(philo);
		else if (philo->state == SLEEP)
			philo = ph_sleep(philo);
	}
	return (NULL);
}

void	ph_write_state(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->pen);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->pen);
		return ;
	}
	time = gettime() - philo->data->start_time;
	if (philo->state == THINK)
		printf("%zu: le philo %d est entrain de penser\n",
			time, philo->id + 1);
	else if (philo->state == EAT)
		printf("%zu: le philo %d est entrain de manger\n",
			time, philo->id + 1);
	else if (philo->state == SLEEP)
		printf("%zu: le philo %d est entrain de dormir\n",
			time, philo->id + 1);
	else if (philo->state == DEAD)
	{
		printf("%zu: le philo %d est mort\n", time, philo->id + 1);
		philo->data->dead = 1;
	}
	pthread_mutex_unlock(&philo->data->pen);
}

void	ft_graille(t_philo *philo, int i)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->pen);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->pen);
		return ;
	}
	time = gettime() - philo->data->start_time;
	if (i == 1)
	{
		printf("%zu: le philo %d a pris une fourchette\n",
			time, philo->id + 1);
	}
	else if (i == 2)
	{
		printf("%zu: le philo %d a pris une fourchettes\n",
			time, philo->id + 1 % philo->data->nb_philo);
	}
	pthread_mutex_unlock(&philo->data->pen);
}

t_philo	*ph_eat(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->data->fork[philo->id]);
		ft_graille(philo, 1);
		pthread_mutex_lock(&philo->data->fork[(philo->id + 1)
			% philo->data->nb_philo]);
		ft_graille(philo, 2);
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork[(philo->id + 1)
			% philo->data->nb_philo]);
		ft_graille(philo, 2);
		pthread_mutex_lock(&philo->data->fork[philo->id]);
		ft_graille(philo, 1);
	}
	ph_write_state(philo);
	philo->meals_eaten++;
	philo->last_meal = gettime();
	philo->state = SLEEP;
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->fork[philo->id]);
	pthread_mutex_unlock(&philo->data->fork[(philo->id + 1)
		% philo->data->nb_philo]);
	return (philo);
}
