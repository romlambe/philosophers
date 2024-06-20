/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:11:56 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/20 11:28:25 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void	*roll_dice()
{
	int value = (rand() % 6) + 1;
	int *result = malloc(sizeof(int));
	*result = value;
	// printf("Value :%d\n", value);
	printf("Thread result: %p\n", result);
	return (void*)result;
}


int main(int ac, char **av)
{
	int	*result;
	srand(time(NULL));
	pthread_t th;
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
		return 1;
	if (pthread_join(th, (void **) &result) != 0)
		return 2;
	printf("Main result: %p\n", result);
	printf ("Result: %d\n", *result);
	free(result);
	return 0;
}

// on peut free la variable créer dans la fonction roll_dice car elle se trouve
// au meme emplacement dans la memoire (si j'ai bien compris)
// si je mets ma variable dans pthread_join c'est pour la recuperer
// si je la mets dans pthread_create c'et pour l'envoyer
