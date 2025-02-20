#include <sys/time.h>
#include <time.h>
#include <stdbool.h>

long long	get_passed_ms(void)
{
	static bool				first_it = true;
	struct timeval			tv;
	static long long		og_ts;

	gettimeofday(&tv, NULL);
	if (first_it)
	{
		og_ts = ((long long)(tv.tv_sec) *1000) + (tv.tv_usec / 1000);
		first_it = false;
	}
	return (((long long)(tv.tv_sec) *1000) + (tv.tv_usec / 1000) - og_ts);
}
