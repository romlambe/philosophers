/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   race_condition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:51:12 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/20 11:12:05 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int mails = 0;

void *routine()
{
	for (int i = 0; i < 10000000; i++)
		mails++;
		//read mails
		//incremente
		//write mails
}

int main()
{
	pthread_t p1, p2;
	if (pthread_create(&p1, NULL, &routine, NULL) != 0)
		return 1;
	if (pthread_create(&p2, NULL, &routine, NULL) != 0)
		return 2;
	if (pthread_join(p1, NULL))
		return 3;
	if (pthread_join(p2, NULL))
		return 4;
	printf ("Number of mails : %d \n", mails);
	return 0;
}
// en gros sans mutex, p1 et p2 ne vont pas s'alterner et donc p2 va incrementer
// à partir de ce qu'à incrementer p1 mais va retourner la valeur ou il a ete bloqué + 1
// ex:	read mail:	23	|	23
//		increment:	23	|	23
//		write mail:	24	|	24

// on avance dans l'execution, p2 est bloqué car p1 est en action
// 		read mail:	29	|	23
//		increment:	29	|	30	-> p2 va incrementer à 30 mais retournera 24
//		write mail:	30	|	24
