/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdursun <mdursun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:41:48 by mdursun           #+#    #+#             */
/*   Updated: 2025/08/17 17:41:48 by mdursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	long	res;

	res = 0;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return ((int)res);
}

void	init_data(int ac, char **av, t_data *data)
{
	data->n_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->meals_required = ft_atoi(av[5]);
	else
		data->meals_required = -1;
}

void	init_philos(t_data *data)
{
	int				i;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;

	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = current_time_ms();
		left = &data->forks[i];
		right = &data->forks[(i + 1) % data->n_philos];
		if (left < right)
		{
			data->philos[i].first_fork = left;
			data->philos[i].second_fork = right;
		}
		else
		{
			data->philos[i].first_fork = right;
			data->philos[i].second_fork = left;
		}
		data->philos[i].data = data;
		i++;
	}
}

int	parse_args(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (0);
	init_data(ac, av, data);
	if (data->n_philos < 1 || data->n_philos > 200
		|| data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
		return (0);
	data->stop_sim = 0;
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->eaten_lock, NULL);
	pthread_mutex_init(&data->death_lock, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->forks || !data->philos)
		return (0);
	while (i < data->n_philos)
		pthread_mutex_init(&data->forks[i++], NULL);
	init_philos(data);
	return (1);
}
