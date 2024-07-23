/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:16:45 by romlambe          #+#    #+#             */
/*   Updated: 2024/07/22 15:58:51 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_time_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_data
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philo;
}					t_data;

//UTILS
int		ft_atoi(const char *nptr);
void	print_message(char *str, t_philo *philo, int id);
void	ft_free(t_data *data, pthread_mutex_t *fork, t_philo *philo);
size_t	get_current_time(void);
int		ft_usleep(size_t millisecond);

//INIT
void	init_input(t_philo *philo, char **av);
void	init_philo(t_philo *philo, t_data *data, pthread_mutex_t *fork,
			char **av);
void	init_fork(pthread_mutex_t *fork, int num_philo);
void	init_data(t_data *data, t_philo *philo);

//THREADS
int		dead_loop(t_philo *philo);
void	*routine(void *pointeur);
int		thread_create(t_data *data, pthread_mutex_t *fork);

//ACTIONS
void	think(t_philo *philo);
void	dream(t_philo *philo);
void	eat(t_philo *philo);

//MONITOR
int		philo_dead(t_philo *philo, size_t time_to_die);
int		check_if_dead(t_philo *philo);
int		check_nb_eat(t_philo *philo);
void	*monitor(void *pointeur);

#endif
