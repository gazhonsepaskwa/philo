#include "../philo.h"

static int	all_meal_eaten(t_table *table, int philo_count)
{
	pthread_mutex_lock(&table->sim_stop_mutex);
	pthread_mutex_lock(&table->eat_count_mutex);
	if (table->occurences != -1
		&& table->eat_count == philo_count * table->occurences)
	{
		table->sim_stop = 1;
		pthread_mutex_unlock(&table->eat_count_mutex);
		pthread_mutex_unlock(&table->sim_stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->eat_count_mutex);
	pthread_mutex_unlock(&table->sim_stop_mutex);
	return (0);
}

int	death(t_table *table)
{
	pthread_mutex_lock(&table->sim_stop_mutex);
	pthread_mutex_lock(&table->death_mutex);
	if (table->death == 1)
	{
		table->sim_stop = 1;
		pthread_mutex_unlock(&table->death_mutex);
		pthread_mutex_unlock(&table->sim_stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->death_mutex);
	pthread_mutex_unlock(&table->sim_stop_mutex);
	return (0);
}

void	*watcher_fct(void *raw_data)
{
	t_table	*table;
	int		philo_count;

	table = (t_table *)raw_data;
	pthread_mutex_lock(&table->philo_count_mutex);
	philo_count = table->philo_count;
	pthread_mutex_unlock(&table->philo_count_mutex);
	while (1)
	{
		if (all_meal_eaten(table, philo_count))
			break ;
		if (death(table))
			break ;
	}
	return (NULL);
}
