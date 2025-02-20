#include "philo.h"

void	take_a_fork(t_philo_data *data, int *next_fork)
{
	int	philo_count;

	pthread_mutex_lock(&data->table->philo_count_mutex);
	philo_count = data->table->philo_count;
	pthread_mutex_unlock(&data->table->philo_count_mutex);
	(*next_fork) = (data->index + 1) % philo_count;
	pthread_mutex_lock(&data->table->forks[data->index]);
	status(data, "has taken a fork");
	pthread_mutex_lock(&data->table->forks[(*next_fork)]);
	status(data, "has taken a fork");
}

long long	routine_eat(t_philo_data *data)
{
	int	time_tmp;
	int	next_fork;

	next_fork = 0;
	take_a_fork(data, &next_fork);
	status(data, "is eating");
	pthread_mutex_lock(&data->table->eat_time_mutex);
	time_tmp = data->table->eat_time;
	pthread_mutex_unlock(&data->table->eat_time_mutex);
	usleep(time_tmp);
	pthread_mutex_unlock(&data->table->forks[data->index]);
	pthread_mutex_unlock(&data->table->forks[next_fork]);
	pthread_mutex_lock(&data->table->eat_count_mutex);
	data->table->eat_count += 1;
	pthread_mutex_unlock(&data->table->eat_count_mutex);
	return (get_timestamp_in_ms());
}

void	routine_sleep(t_philo_data *data)
{
	int	time_tmp;

	status(data, "is sleeping");
	pthread_mutex_lock(&data->table->sleep_time_mutex);
	time_tmp = data->table->sleep_time;
	pthread_mutex_unlock(&data->table->sleep_time_mutex);
	usleep(time_tmp);
}

void	routine_think(t_philo_data *data)
{
	status(data, "is thinking");
}
