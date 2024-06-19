/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:16:35 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/18 17:29:26 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* routine()
{
	printf("Test from threads\n");
	sleep(3);
	printf("Ending thread\n");
}

int main(int ac, char **av)
{
	pthread_t	t1, t2;
	if (pthread_create(&t1, NULL, &routine, NULL)!= 0)
		return 1;
	if (pthread_create(&t2, NULL, &routine, NULL)!= 0)
		return 2;
	if (pthread_join(t1, NULL) != 0)
		return 3;
	if (pthread_join(t2, NULL) != 0)
		return 4;
	return 0;
}
//pthread_create peut retourner 0 ou une valeur d'erreur

