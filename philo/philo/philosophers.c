/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdursun <mdursun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:42:30 by mdursun           #+#    #+#             */
/*   Updated: 2025/08/17 17:42:30 by mdursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_forks(t_philo *ph)
{
	pthread_mutex_lock(ph->first_fork);
	print_status(ph, "has taken a fork");
	pthread_mutex_lock(ph->second_fork);
	print_status(ph, "has taken a fork");
	pthread_mutex_lock(&ph->data->death_lock);
	ph->last_meal = current_time_ms();
	pthread_mutex_unlock(&ph->data->death_lock);
	print_status(ph, "is eating");
	ft_usleep(ph->data->time_to_eat);
}

int	is_sim_over(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->death_lock);
	res = data->stop_sim;
	pthread_mutex_unlock(&data->death_lock);
	return (res);
}

int	one_philo(t_philo *ph)
{
	if (ph->data->n_philos == 1)
	{
		pthread_mutex_lock(ph->first_fork);
		print_status(ph, "has taken a fork");
		while (!is_sim_over(ph->data))
			ft_usleep(10);
		pthread_mutex_unlock(ph->first_fork);
		return (1);
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (one_philo(ph))
		return (NULL);
	if (ph->id % 2 != 0)
		ft_usleep(100);
	while (!is_sim_over(ph->data))
	{
		print_status(ph, "is thinking");
		get_forks(ph);
		pthread_mutex_lock(&ph->data->eaten_lock);
		ph->meals_eaten++;
		pthread_mutex_unlock(&ph->data->eaten_lock);
		pthread_mutex_unlock(ph->first_fork);
		pthread_mutex_unlock(ph->second_fork);
		print_status(ph, "is sleeping");
		ft_usleep(ph->data->time_to_sleep);
	}
	return (NULL);
}
