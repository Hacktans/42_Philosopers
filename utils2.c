/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 07:08:01 by hadalici          #+#    #+#             */
/*   Updated: 2025/08/25 08:29:13 by hadalici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(data->print_lock);
	pthread_mutex_destroy(data->meal_lock);
	pthread_mutex_destroy(data->death_lock);
	free(data->forks);
	free(data->print_lock);
	free(data->meal_lock);
	free(data->death_lock);
	free(data->philo);
	free(data);
}

int	set_dead_flag(t_data *data, long long since_meal, int i)
{
	if (since_meal > data->time_to_die)
	{
		pthread_mutex_lock(data->death_lock);
		data->dead_flag = 1;
		pthread_mutex_unlock(data->death_lock);
		pthread_mutex_lock(data->print_lock);
		if (data->num_philos != 1)
			printf("%lld %d died\n", get_time() - data->start_time,
				data->philo[i].id);
		pthread_mutex_unlock(data->print_lock);
		return (0);
	}
	return (1);
}

int	get_meal_c(t_philo *philo)
{
	int	meal_count;

	pthread_mutex_lock(philo->data->meal_lock);
	meal_count = philo->meal_c;
	pthread_mutex_unlock(philo->data->meal_lock);
	return (meal_count);
}
