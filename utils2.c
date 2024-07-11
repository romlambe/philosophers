/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:10:45 by romlambe          #+#    #+#             */
/*   Updated: 2024/07/11 14:52:54 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*ph_sleep(t_philo *philo)
{
	ph_write_state(philo);
	usleep(philo->data->time_to_sleep * 1000);
	philo->state = THINK;
	return (philo);
}
