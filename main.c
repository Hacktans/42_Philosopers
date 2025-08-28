/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 07:03:09 by hadalici          #+#    #+#             */
/*   Updated: 2025/08/25 08:44:03 by hadalici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_philo	*philo;
	int		meal_count;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
		return (one_philo(philo), (void *)0);
	while (1)
	{
		if (philo->id % 2 == 0)
			usleep(100);
		if (philo->data->max_meals != -1)
		{
			meal_count = get_meal_c(philo);
			if (meal_count >= philo->data->max_meals)
				break ;
		}
		if (is_eating(philo) == 1)
			break ;
		is_sleeping(philo);
		if (is_dead(philo))
			break ;
		is_thinking(philo);
	}
	return (NULL);
}

static void	*dead_monitor(void *arg)
{
	t_data		*data;
	int			i;
	long long	since_meal;
	int			meal_count;

	data = (t_data *)arg;
	i = 0;
	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(data->meal_lock);
			since_meal = get_time() - data->philo[i].last_meal;
			meal_count = data->philo[i].meal_c;
			pthread_mutex_unlock(data->meal_lock);
			if (!set_dead_flag(data, since_meal, i))
				return (NULL);
			if (data->max_meals != -1 && meal_count >= data->max_meals)
				return (NULL);
			i++;
		}
		usleep(600);
	}
}

static void	create_and_wait(t_data *data)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, &dead_monitor, data);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

static void	start_thread(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philo)
		return ;
	data->start_time = get_time();
	while (i < data->num_philos)
	{
		philo = &data->philo[i];
		philo->id = i + 1;
		philo->data = data;
		philo->left_fork = i;
		philo->right_fork = (i + 1) % data->num_philos;
		philo->meal_c = 0;
		philo->last_meal = get_time();
		data->dead_flag = 0;
		i++;
	}
	create_and_wait(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (!parse(ac, av, data))
	{
		free(data);
		return (0);
	}
	init_mutex(data);
	start_thread(data);
	destroy_mutex(data);
	return (0);
}
