#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>

// utils
#include "srcs/utils/utils.h"

#define FORK "has taken a fork"
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define CUTE 0

// philos data
typedef struct s_philo_data
{
	int				id;
	long long		last_meal;
	struct s_table	*t;
}					t_philo_data;

// table
typedef struct s_table
{
	pthread_mutex_t	main;
	pthread_mutex_t	print;
	unsigned int	philo_count;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	unsigned int	death_time;
	size_t			max_iter;
	pthread_t		*philos;
	t_philo_data	**philos_d;
	pthread_mutex_t	*forks;
}					t_table;

//init
t_table *init(char **av);
int		create_philos(t_table *table);
int		join_philos(t_table *table);

// habit
void	habit_eat(t_philo_data *d);
void	habit_sleep(t_philo_data *d);
void	habit_think(t_philo_data *d);
#endif
