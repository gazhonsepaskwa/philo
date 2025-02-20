#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>

// utils
#include "srcs/utils/utils.h"

// philos data
typedef struct s_philo_data
{
	int				index;
	struct s_table	*table;
}					t_philo_data;

// table
typedef struct s_table
{
	pthread_t		*philos;
	pthread_mutex_t	*forks;
}					t_table;

#endif
