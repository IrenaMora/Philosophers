#include "philosophers.h"

int	main(int args_count, char **args)
{
	t_philosophers	*philosophers;

	if (validate_args(args_count, args) == STATUS_FAIL)
		return (EXIT_FAILURE);
	if (!philosophers_malloc(&philosophers, args[1]))
	{
		define_error(ERROR_MALLOC);
		return (EXIT_FAILURE);
	}
	philosophers_parse_args(args_count, args, philosophers);
	philosophers_create_mutex(philosophers);
	gettimeofday(&philosophers->global_time, NULL);
	philosophers->is_exit = 0;
	philosophers_create_threads(philosophers);
	while (!philosophers->is_exit)
		usleep(4 * MICROSECOND_IN_MILLISECOND);
	philosophers_dealloc(philosophers);
	return (EXIT_SUCCESS);
}
