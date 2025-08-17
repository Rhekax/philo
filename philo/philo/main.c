/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdursun <mdursun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:42:27 by mdursun           #+#    #+#             */
/*   Updated: 2025/08/17 22:45:31 by mdursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_eaten(t_data *data, int done)
{
	pthread_mutex_lock(&data->death_lock);
	if (data->meals_required > 0 && done == data->n_philos)
		data->stop_sim = 1;
	pthread_mutex_unlock(&data->death_lock);
}

void	death(t_data *data, t_philo *p)
{
	pthread_mutex_lock(&data->death_lock);
	pthread_mutex_lock(&data->print_lock);
	if ((current_time_ms() - p->last_meal) > data->time_to_die
		&& !data->stop_sim)
	{
		printf("%lld %d died\n", time_since_start(data), p->id + 1);
		data->stop_sim = 1;
	}
	pthread_mutex_unlock(&data->print_lock);
	pthread_mutex_unlock(&data->death_lock);
}

void	monitor(t_data *data)
{
	int		i;
	int		done;
	t_philo	*p;

	while (!data->stop_sim)
	{
		i = -1;
		done = 0;
		while (++i < data->n_philos)
		{
			p = &data->philos[i];
			death(data, p);
			pthread_mutex_lock(&data->eaten_lock);
			if (data->meals_required > 0
				&& p->meals_eaten >= data->meals_required)
				done++;
			pthread_mutex_unlock(&data->eaten_lock);
		}
		check_eaten(data, done);
		ft_usleep(1);
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	if (!parse_args(ac, av, &data))
	{
		printf("Error : Invalid arguments\n");
		return (1);
	}
	data.start_time = current_time_ms();
	while (i < data.n_philos)
	{
		pthread_create(&data.philos[i].thread,
			NULL, philo_routine, &data.philos[i]);
		i++;
	}
	monitor(&data);
	i = 0;
	while (i < data.n_philos)
		pthread_join(data.philos[i++].thread, NULL);
	cleanup(&data);
	return (0);
}
