/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:24:15 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/18 16:43:24 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	int	ttd;
	int	tte;
	int	tts;
}				t_philo;

int	handle_error_arg(int ac, char **av);
int	ft_atoi(const char *nptr);
int	ft_isdigit(char **av);
