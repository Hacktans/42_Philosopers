/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 07:03:06 by hadalici          #+#    #+#             */
/*   Updated: 2025/08/25 08:44:53 by hadalici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				left_fork;
	int				right_fork;
	long long		last_meal;
	int				meal_c;
	struct s_data	*data;
}t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				max_meals;
	int				dead_flag;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*death_lock;
	t_philo			*philo;
}t_data;

int			parse(int ac, char **av, t_data *data);
int			ft_atol(const char *str);
long long	get_time(void);
void		is_thinking(t_philo *philo);
void		print_action(t_philo *philo, char *str);
int			is_eating(t_philo *philo);
void		is_sleeping(t_philo *philo);
void		init_mutex(t_data *data);
int			is_dead(t_philo *phlio);
void		one_philo(t_philo *philo);
void		my_usleep(t_philo *philo, long long sleep_time);
void		destroy_mutex(t_data *data);
int			set_dead_flag(t_data *data, long long since_meal, int i);
int			get_meal_c(t_philo *philo);

#endif