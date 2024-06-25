/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_argument_threads.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:30:13 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/20 11:52:47 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void *routine(void *arg)
{
	// sleep(1);
	int index = *(int *)arg;
	printf("%d ", primes[index]);
	free(arg);
}

int main(int ac, char **av)
{
	pthread_t	th[10];
	int i;
	for(i = 0; i < 10; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			perror("Failed to create thread");

	}

	for(i = 0; i < 10; i++)
	{
		if (pthread_join(th[i], NULL)!= 0)
			perror("Failed to joined thread");
	}
	return 0;
}
