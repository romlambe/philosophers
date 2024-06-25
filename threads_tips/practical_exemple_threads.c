/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practical_exemple_threads.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:00:55 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/20 12:18:03 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void *routine(void *arg)
{
	int index = *(int *)arg;
	int sum = 0;
	for (int i = 0; i < 5; i++)
		sum += primes[index + i];
	printf("Local sum %d\n", sum);
	*(int*)arg = sum;
	return (arg);
}

int main(int ac, char **av)
{
	pthread_t	th[2];
	int i;
	for(i = 0; i < 2; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			perror("Failed to create thread");

	}
	int globalSum = 0;
	for(i = 0; i < 2; i++)
	{
		int *result;
		if (pthread_join(th[i], (void **)&result)!= 0)
			perror("Failed to joined thread");
		globalSum += *result;
		free(result);
	}
	printf("GlobalSum: %d\n", globalSum);
	return 0;
}
