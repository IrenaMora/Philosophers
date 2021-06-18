#include "philosophers.h"

void	ft_usleep(int microsecond, t_philosophers *philosophers, \
int philosopher_number, struct timeval *time)
{
	int				different;
	struct timeval	first_time;
	struct timeval	new_time;

	gettimeofday(&first_time, NULL);
	while (1)
	{
		usleep(MIN_TIME);
		if (philosopher_number != NOT_CHECK)
			check_for_death(philosophers, philosopher_number, time, 0);
		gettimeofday(&new_time, NULL);
		different = MICROSECONDS_IN_SECOND * (new_time.tv_sec - first_time.tv_sec) \
		+ (new_time.tv_usec - first_time.tv_usec);
		if (different >= microsecond)
			return ;
	}
}

long long	get_time_different(struct timeval *last_time, int update_last_time)
{
	struct timeval	new_time;
	int				different;

	gettimeofday(&new_time, NULL);
	different = MICROSECONDS_IN_SECOND * (new_time.tv_sec - last_time->tv_sec) \
	+ (new_time.tv_usec - last_time->tv_usec);
	if (update_last_time)
	{
		last_time->tv_usec = new_time.tv_usec;
		last_time->tv_sec = new_time.tv_sec;
	}
	return (different);
}

long long	get_global_time(t_philosophers *philosophers)
{
	long long	different;

	different = get_time_different(&philosophers->global_time, 0);
	return (different / MILLISECONDS_IN_SECOND);
}

void	check_for_death(t_philosophers *philosophers, int philosopher_number, \
struct timeval *time, int update_last_time)
{
	int	different;

	different = get_time_different(time, update_last_time);
	if (different >= philosophers->time_dead)
	{
		if (!philosophers->is_exit)
			printf("%lld %d died\n", get_global_time(philosophers), \
			philosopher_number);
		philosophers->is_exit = 1;
	}
}
