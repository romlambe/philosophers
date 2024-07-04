/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:24:15 by romlambe          #+#    #+#             */
/*   Updated: 2024/07/04 15:47:50 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define THINK 0
#define EAT 1
#define SLEEP 2
#define DEAD 3

typedef struct s_philo
{
	pthread_t		*thread;
	int				id;
	int				state;
	int				dead;
	int				meals_eaten;
	size_t			last_meal;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				nb_eat;
	int				dead;
	t_philo			**philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_mutex_t	pen;
	pthread_mutex_t	*fork;
}					t_data;

//Utils
size_t	gettime(void);
void	ft_usleep(size_t time);
void	ft_free(t_data *data);

//Create Threads
void	*state_thread_philo(void *arg);
void	ph_write_state(t_philo *philo);
t_philo	*ph_sleep(t_philo *philo);
t_philo	*ph_eat(t_philo *philo);
void	*state_thread_philo(void *arg);
void	*create_thread(t_data *data);

//Handle Errors
int		handle_error_arg(int ac, char **av);
int		ft_atoi(const char *nptr);
int		ft_isdigit(char **av);

//Init
t_data	*init_philo(t_data *data);
