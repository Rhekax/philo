/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdursun <mdursun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:42:39 by mdursun           #+#    #+#             */
/*   Updated: 2025/08/17 17:42:39 by mdursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo {
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_data			*data;
}	t_philo;

struct s_data {
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	long long		start_time;
	int				stop_sim;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	eaten_lock;
	t_philo			*philos;
};

void		init_philos(t_data *data);
void		*philo_routine(void *arg);
int			parse_args(int ac, char **av, t_data *data);
void		monitor_loop(t_data *data);
void		cleanup(t_data *data);
void		init_data(int ac, char **av, t_data *data);
int			one_philo(t_philo *ph);
long long	current_time_ms(void);
long long	time_since_start(t_data *data);
void		print_status(t_philo *ph, const char *msg);
int			is_sim_over(t_data *data);
void		ft_usleep(long long milliseconds);
void		check_eaten(t_data *data, int done);
void		death(t_data *data, t_philo *p);
int			ft_atoi(const char *str);
int			is_number(const char *str);
int			ft_parse(int ac, char **av);

#endif
