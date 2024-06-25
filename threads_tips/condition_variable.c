/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:37:04 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/20 16:01:34 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
int fuel = 0;

void *fuel_filling(void *arg)
{
	for (int i = 0; i < 5; i++)
	{
		pthread_mutex_lock(&mutexFuel);
		fuel += 15;
		printf("Filling fuel... %d\n", fuel);
		pthread_mutex_unlock(&mutexFuel);
		pthread_cond_signal(&condFuel);
		sleep(1);
	}
}

void *car(void *arg)
{
	pthread_mutex_lock(&mutexFuel);
	while (fuel < 40)
	{
		printf("No fuel. Waiting...\n");
		pthread_cond_wait(&condFuel, &mutexFuel);
	}
	fuel -= 40;
	printf("Got fuel. Now left... %d\n", fuel);
	printf("No fuel...\n");
	pthread_mutex_unlock(&mutexFuel);
}

int main(int ac, char **av)
{
	pthread_t th[2];
	pthread_mutex_init(&mutexFuel, NULL);
	pthread_cond_init(&condFuel, NULL);
	for (int i = 0; i < 2; i++)
	{
		if (i == 1)
		{
			if (pthread_create(&th[i], NULL, &fuel_filling, NULL ) != 0)
				perror ("Failed to create threads");
		}
		else
		{
			if (pthread_create(&th[i], NULL, &car, NULL ) != 0)
				perror ("Failed to create threads");
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (pthread_join(th[i], NULL))
			perror ("Failed to joined");
	}
	pthread_mutex_destroy(&mutexFuel);
	pthread_cond_destroy(&condFuel);
	return 0;
}
