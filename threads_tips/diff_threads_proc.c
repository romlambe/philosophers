/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_threads_proc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:31:43 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/19 15:10:42 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>

int	x = 2;

void	*routine()
{
	x++;
	sleep(2);
	printf ("Value of x: %d\n", x);
}

void	*routine2()
{
	sleep(2);
	printf ("Value of x: %d\n", x);
}

int main(int ac, char **av)
{
	pthread_t t1;
	pthread_t t2;
	if (pthread_create(&t1, NULL, &routine, NULL))
		return 1;
	if (pthread_create(&t2, NULL, &routine2, NULL))
		return 2;
	if (pthread_join(t1, NULL))
		return 3;
		if (pthread_join(t2, NULL))
		return 4;
	return 0;
}

// int main(int ac, char **av)
// {
// 	int x = 2;
// 	int pid = fork();
// 	if (pid == -1)
// 		return 1;
// 	if (pid == 0)
// 		x++;
// 	sleep(2);
// 	printf ("Value of x: %d\n", x);
// 	if (pid != 0)
// 		wait(NULL);
// 	return 0;
// }

//si on touche à une valeur dans une thread, elle sera changé dans un autre
