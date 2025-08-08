#include "philosophers.h"

void monitor(t_data *data)
{
	int i, done;

	while (!data->stop_sim)
	{
		i = -1;
		done = 0;

		while (++i < data->n_philos)
		{
			t_philo *p = &data->philos[i];

			pthread_mutex_lock(&data->death_lock);
			if ((current_time_ms() - p->last_meal) > data->time_to_die && !data->stop_sim)
			{
				pthread_mutex_lock(&data->print_lock);
				printf("%lld %d died\n", time_since_start(data), p->id + 1);
				data->stop_sim = 1;
				pthread_mutex_unlock(&data->print_lock);	
			}
			pthread_mutex_unlock(&data->death_lock);

			if (data->meals_required > 0 && p->meals_eaten >= data->meals_required)
				done++;
		}
		if (data->meals_required > 0 && done == data->n_philos)
			data->stop_sim = 1;

		ft_usleep(1);
	}
}

int main(int ac, char **av)
{
	t_data data;

	if (!parse_args(ac, av, &data))
		return (1);

	data.start_time = current_time_ms();

	for (int i = 0; i < data.n_philos; i++)
		pthread_create(&data.philos[i].thread, NULL, philo_routine, &data.philos[i]);

	monitor(&data);
	for (int i = 0; i < data.n_philos; i++)
		pthread_join(data.philos[i].thread, NULL);

	cleanup(&data);
	return (0);
}
