/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 07:03:11 by hadalici          #+#    #+#             */
/*   Updated: 2025/08/25 08:44:21 by hadalici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_thinking(t_philo *philo)
{
	print_action(philo, "is thinking");
}

static int	even_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	if (!is_dead(philo))
	{
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		if (!is_dead(philo))
			print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return (1);
	}
	return (0);
}

static int	odd_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	if (!is_dead(philo))
	{
		usleep(200);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		if (!is_dead(philo))
			print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		return (1);
	}
	return (0);
}

int	is_eating(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	if (philo->id % 2 == 0)
	{
		if (even_philo(philo) == 1)
			return (1);
	}
	else
	{
		if (odd_philo(philo) == 1)
			return (1);
	}
	print_action(philo, "is eating");
	pthread_mutex_lock(philo->data->meal_lock);
	philo->last_meal = get_time();
	philo->meal_c++;
	pthread_mutex_unlock(philo->data->meal_lock);
	my_usleep(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	return (0);
}

void	is_sleeping(t_philo *philo)
{
	print_action(philo, "is sleeping");
	my_usleep(philo, philo->data->time_to_sleep);
}
