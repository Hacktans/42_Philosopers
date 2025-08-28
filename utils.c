/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 07:02:59 by hadalici          #+#    #+#             */
/*   Updated: 2025/08/25 11:47:58 by hadalici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(t_philo *philo, long long sleep_time)
{
	long long	wake_time;

	wake_time = get_time() + sleep_time;
	while (get_time() < wake_time)
	{
		pthread_mutex_lock(philo->data->death_lock);
		if (philo->data->dead_flag)
		{
			pthread_mutex_unlock(philo->data->death_lock);
			break ;
		}
		pthread_mutex_unlock(philo->data->death_lock);
		usleep(100);
	}
}

long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	return (time);
}

void	print_action(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->data->print_lock);
	pthread_mutex_lock(philo->data->death_lock);
	if (philo->data->dead_flag == 0)
		printf("%lld %d %s\n", get_time() - philo->data->start_time,
			philo->id, str);
	pthread_mutex_unlock(philo->data->death_lock);
	pthread_mutex_unlock(philo->data->print_lock);
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	data->print_lock = malloc(sizeof(pthread_mutex_t));
	data->meal_lock = malloc(sizeof(pthread_mutex_t));
	data->death_lock = malloc(sizeof(pthread_mutex_t));
	if (!data->forks || !data->print_lock
		|| !data->meal_lock || !data->death_lock)
		return ;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(data->print_lock, NULL);
	pthread_mutex_init(data->meal_lock, NULL);
	pthread_mutex_init(data->death_lock, NULL);
}

int	is_dead(t_philo *phlio)
{
	int	is_dead;

	pthread_mutex_lock(phlio->data->death_lock);
	is_dead = phlio->data->dead_flag;
	pthread_mutex_unlock(phlio->data->death_lock);
	return (is_dead);
}
