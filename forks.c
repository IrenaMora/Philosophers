#include "philosophers.h"

void	put_forks(t_philosophers *philosophers, int philosopher_number)
{
	pthread_mutex_t	*my_fork;
	pthread_mutex_t	*right_fork;

	my_fork = &philosophers->forks[philosopher_number - 1];
	if (philosopher_number == philosophers->philosophies_count)
		right_fork = &philosophers->forks[0];
	else
		right_fork = &philosophers->forks[philosopher_number];
	pthread_mutex_unlock(my_fork);
	pthread_mutex_unlock(right_fork);
}

void	take_forks(t_philosophers *philosophers, int philosopher_number, \
struct timeval *time)
{
	pthread_mutex_t	*my_fork;
	pthread_mutex_t	*right_fork;

	my_fork = &philosophers->forks[philosopher_number - 1];
	if (philosopher_number == philosophers->philosophies_count)
		right_fork = &philosophers->forks[0];
	else
		right_fork = &philosophers->forks[philosopher_number];
	pthread_mutex_lock(my_fork);
	pthread_mutex_lock(right_fork);
	check_for_death(philosophers, philosopher_number, time, 1);
	if (!philosophers->is_exit)
	{
		printf("%lld %d has taken a fork\n", get_global_time(philosophers), \
		philosopher_number);
		printf("%lld %d has taken a fork\n", get_global_time(philosophers), \
		philosopher_number);
	}
}
