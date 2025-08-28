/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadalici <hadalici@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 07:24:14 by hadalici          #+#    #+#             */
/*   Updated: 2025/08/25 08:43:44 by hadalici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atol(const char *str)
{
	int		i;
	int		c;
	long	result;

	result = 0;
	i = 0;
	c = 1;
	if (str[0] == '0')
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			c *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		if (result > 2147483647)
			return (0);
		i++;
	}
	return (result * c);
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_action(philo, "has taken a fork");
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	printf("%lld %d died\n", get_time() - philo->data->start_time,
		philo->data->philo[0].id);
}

static int	int_chk(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '+' || av[i][j] == '-')
			j++;
		if (av[i][j] == '\0' || av[i][j] == '-')
			return (0);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	num_chk(char **av, t_data *data)
{
	data->num_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->max_meals = ft_atol(av[5]);
	else
		data->max_meals = -1;
	if (data->num_philos < 1 || data->time_to_die < 1
		|| data->time_to_eat < 1 || data->time_to_sleep < 1)
		return (0);
	if (data->num_philos > 200)
		return (0);
	return (1);
}

int	parse(int ac, char **av, t_data *data)
{
	if (!(ac == 5 || ac == 6))
	{
		printf("Please enter five or six arguments\n");
		return (0);
	}
	if (!int_chk(av))
	{
		printf ("Please enter only numeric arguments\n");
		return (0);
	}
	if (!num_chk(av, data))
	{
		if (data->num_philos > 200)
		{
			printf("Philosopher number must be between 1 and 200\n");
			return (0);
		}
		printf("Please enter only positive and integer arguments\n");
		return (0);
	}
	return (1);
}
