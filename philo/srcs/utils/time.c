#include "../../philo.h"
#include <sys/time.h>
#include <time.h>

long long	get_timestamp_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long long)(tv.tv_sec) *1000) + (tv.tv_usec / 1000));
}
