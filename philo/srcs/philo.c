#include "../philo.h"
#include "utils/utils.h"

void	status(t_philo_data *data, char *message)
{
	pthread_mutex_lock(&data->table->print_mutex);
	printf("%lld %d %s\n", get_timestamp_in_ms(), data->index, message);
	pthread_mutex_unlock(&data->table->print_mutex);
}

void	wait_if_odd(t_philo_data *data)
{
	int	tmp_time;

	if (data->index % 2 != 0)
	{
		pthread_mutex_lock(&data->table->eat_time_mutex);
		tmp_time = data->table->eat_time;
		pthread_mutex_unlock(&data->table->eat_time_mutex);
		usleep(tmp_time / 2);
	}
}

int	routine_end(t_philo_data *data, long long last_meal)
{
	int			sim_stop;

	pthread_mutex_lock(&data->table->sim_stop_mutex);
	sim_stop = data->table->sim_stop;
	pthread_mutex_unlock(&data->table->sim_stop_mutex);
	if (sim_stop)
		return (1);
	pthread_mutex_lock(&data->table->die_time_mutex);
	pthread_mutex_lock(&data->table->death_mutex);
	if (get_timestamp_in_ms() - last_meal > data->table->die_time) // why are they not fucking dying ??????? (I' m gonna check this later to dont kill anyone :) )
	{
		data->table->death = 1;
		pthread_mutex_unlock(&data->table->die_time_mutex);
		pthread_mutex_unlock(&data->table->death_mutex);
		status(data, "died");
		return (1);
	}
	pthread_mutex_unlock(&data->table->die_time_mutex);
	pthread_mutex_unlock(&data->table->death_mutex);
	return (0);
}

void	*philo(void *raw_data)
{
	t_philo_data	*data;
	long long		last_meal;

	data = (t_philo_data *)raw_data;
	wait_if_odd(data);
	last_meal = 0;
	while (1)
	{
		last_meal = routine_eat(data);
		if (routine_end(data, last_meal))
			break ;
		routine_sleep(data);
		if (routine_end(data, last_meal))
			break ;
		routine_think(data);
		if (routine_end(data, last_meal))
			break ;
	}
	return (NULL);
}
