/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:27:47 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/18 16:47:48 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	handle_error_arg(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 4 &&  ac > 5)
		return (1);
	if (ft_isdigit(av) == 1)
		return (1);
	return (0);
}

int main(int ac, char **av)
{
	if (handle_error_arg(ac, av) == 1)
		printf ("t nul bouffon\n");
	
	return (0);
}
