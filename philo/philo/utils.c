/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdursun <mdursun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:42:32 by mdursun           #+#    #+#             */
/*   Updated: 2025/08/17 17:42:32 by mdursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->death_lock);
	free(data->forks);
	free(data->philos);
}

long long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

long long	time_since_start(t_data *data)
{
	return (current_time_ms() - data->start_time);
}

void	print_status(t_philo *ph, const char *msg)
{
	if (!is_sim_over(ph->data))
	{
		pthread_mutex_lock(&ph->data->print_lock);
		printf("%lld %d %s\n", time_since_start(ph->data), ph->id + 1, msg);
		pthread_mutex_unlock(&ph->data->print_lock);
	}
}

void	ft_usleep(long long milliseconds)
{
	long long	start;

	start = current_time_ms();
	while ((current_time_ms() - start) < milliseconds)
		usleep(100);
}
