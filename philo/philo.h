#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

// utils
#include "srcs/utils/utils.h"

#define FORK "has taken a fork"
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define DIED "\e[31mdied\e[0m              "
#define CUTE 1

// philos data
typedef struct s_philo_data
{
	int				id;
	long long		last_meal;
	pthread_mutex_t	lm_lock;
	struct s_table	*t;
}					t_philo_data;

// table
typedef struct s_table
{
	// pthread_mutex_t	main;
	pthread_mutex_t	print;
	unsigned int	philo_count;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	unsigned int	death_time;
	size_t			max_iter;
	pthread_t		*philos;
	pthread_t		watcher;
	t_philo_data	**philos_d;
	pthread_mutex_t	*forks;
	pthread_mutex_t	sim_s_lock;
	bool			simstop;
	pthread_mutex_t	done_lock;
	unsigned int	done;
}					t_table;

//init
t_table *init(char **av);
int		create_philos(t_table *table);
int		create_watcher(t_table *table);
int		join_philos(t_table *table);
int		join_watcher(t_table *table);

// habit
bool	habit_eat(t_philo_data *d);
bool	habit_sleep(t_philo_data *d);
bool	habit_think(t_philo_data *d);
bool	status(t_philo_data *data, char *msg);

// wait 
void wait_end(t_table *table);

#endif
