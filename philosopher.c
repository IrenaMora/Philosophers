#include "philosophers.h"

void	check_eating_max(t_philosophers *philosophers)
{
	int	position;

	position = 0;
	while (position < philosophers->philosophies_count)
	{
		if (philosophers->eating_memory[position] < philosophers->eating_max)
			return ;
		position++;
	}
	philosophers->is_exit = 1;
}

void	philosopher_eat(t_philosophers *philosophers, int philosopher_number, \
struct timeval *time)
{
	if (philosophers->eating_max != NOT_CHECK)
	{
		check_eating_max(philosophers);
		philosophers->eating_memory[philosopher_number - 1] += 1;
	}
	if (!philosophers->is_exit)
		printf("%lld %d is eating\n", get_global_time(philosophers), \
		philosopher_number);
	if (philosophers->eating_max != NOT_CHECK)
		check_eating_max(philosophers);
	ft_usleep(philosophers->time_eat, philosophers, philosopher_number, time);
}

void	philosopher_sleep(t_philosophers *philosophers, \
int philosopher_number, struct timeval *time)
{
	if (!philosophers->is_exit)
		printf("%lld %d is sleeping\n", get_global_time(philosophers), \
		philosopher_number);
	ft_usleep(philosophers->time_sleep, philosophers, philosopher_number, time);
}

void	philosopher_think(t_philosophers *philosophers, int philosopher_number)
{
	if (!philosophers->is_exit)
		printf("%lld %d is thinking\n", get_global_time(philosophers), \
		philosopher_number);
}

void	*alive_philosophers(void *arg)
{
	int				philosopher_number;
	struct timeval	philosopher_time;
	t_philosophers	*philosophers;

	philosophers = (t_philosophers *)arg;
	philosopher_number = philosophers->number + 1;
	philosophers->already = 0;
	gettimeofday(&philosopher_time, NULL);
	if (philosophers->philosophies_count == 1)
	{
		ft_usleep(philosophers->time_dead, NULL, NOT_CHECK, NULL);
		check_for_death(philosophers, philosopher_number, &philosopher_time, 1);
	}
	while (1)
	{
		take_forks(philosophers, philosopher_number, &philosopher_time);
		philosopher_eat(philosophers, philosopher_number, &philosopher_time);
		put_forks(philosophers, philosopher_number);
		philosopher_sleep(philosophers, philosopher_number, &philosopher_time);
		philosopher_think(philosophers, philosopher_number);
	}
}
