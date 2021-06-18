#include "philosophers.h"

void	*philosophers_malloc(t_philosophers **philosophers, \
char *philosophers_count)
{
	int	philosophers_c;

	philosophers_c = ft_atoi(philosophers_count, ATOI_PHILOSOPHER);
	(*philosophers) = malloc(sizeof(t_philosophers));
	if (!(*philosophers))
		return (NULL);
	(*philosophers)->threads = malloc(sizeof(pthread_t) * philosophers_c);
	if (!((*philosophers)->threads))
	{
		free(*philosophers);
		return (NULL);
	}
	(*philosophers)->forks = malloc(sizeof(pthread_mutex_t) * philosophers_c);
	if (!((*philosophers)->threads))
	{
		free(*philosophers);
		free((*philosophers)->threads);
		return (NULL);
	}
	return (*philosophers);
}

void	philosophers_parse_args(int args_count, char **args, \
t_philosophers *philosophers)
{
	int	position;

	position = 0;
	philosophers->philosophies_count = ft_atoi(args[1], ATOI_PHILOSOPHER);
	philosophers->time_dead = ft_atoi(args[2], ATOI_TIME) * MICROSECOND_IN_MILLISECOND \
	+ 1 * MICROSECOND_IN_MILLISECOND;
	philosophers->time_eat = ft_atoi(args[3], ATOI_TIME) \
	* MICROSECOND_IN_MILLISECOND;
	philosophers->time_sleep = ft_atoi(args[4], ATOI_TIME) \
	* MICROSECOND_IN_MILLISECOND;
	philosophers->eating_max = NOT_CHECK;
	if (args_count == MAX_ARGS_COUNT)
	{
		philosophers->eating_memory = malloc(philosophers->philosophies_count);
		philosophers->eating_max = ft_atoi(args[MAX_ARGS_COUNT - FIRST_ARG], \
		ATOI_EATING_TIME);
		while (position < philosophers->philosophies_count)
			philosophers->eating_memory[position++] = BY_DEFAULT;
	}
}

void	philosophers_create_mutex(t_philosophers *philosophers)
{
	int	position;

	position = 0;
	while (position < philosophers->philosophies_count)
		pthread_mutex_init(&philosophers->forks[position++], NULL);
}

void	philosophers_create_threads(t_philosophers *philosophers)
{
	int	position;

	position = 0;
	while (position < philosophers->philosophies_count)
	{
		philosophers->already = 1;
		philosophers->number = position;
		pthread_create(&philosophers->threads[position++], NULL, \
		alive_philosophers, philosophers);
		while (philosophers->already && position)
			;
	}
}

void	philosophers_dealloc(t_philosophers *philosophers)
{
	int	position;

	position = 0;
	while (position < philosophers->philosophies_count)
		pthread_detach(philosophers->threads[position++]);
	position = 0;
	while (position < philosophers->philosophies_count)
		pthread_mutex_destroy(&philosophers->forks[position++]);
	free(philosophers->threads);
	free(philosophers->forks);
	free(philosophers->eating_memory);
	free(philosophers);
}
