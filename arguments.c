#include "philosophers.h"

int	check_args_count(int args_count)
{
	if (args_count < MIN_ARGS_COUNT || args_count > MAX_ARGS_COUNT)
	{
		define_error(ERROR_WRONG_ARGS_COUNT);
		return (STATUS_FAIL);
	}
	return (STATUS_SUCCESS);
}

int	check_args(int args_count, char **args)
{
	int		position;
	char	*philosophers;

	philosophers = args[1];
	if (ft_atoi(philosophers, ATOI_PHILOSOPHER) == STATUS_FAIL)
		return (STATUS_FAIL);
	position = START_ARG_FOR_TIMES;
	while (position < args_count && position < MAX_ARGS_COUNT - FIRST_ARG)
	{
		if (ft_atoi(args[position++], ATOI_TIME) == STATUS_FAIL)
			return (STATUS_FAIL);
	}
	if (args_count == MAX_ARGS_COUNT && ft_atoi(args[position], \
	ATOI_EATING_TIME) == STATUS_FAIL)
		return (STATUS_FAIL);
	return (STATUS_SUCCESS);
}

int	validate_args(int args_count, char **args)
{
	if (check_args_count(args_count) == STATUS_FAIL)
		return (STATUS_FAIL);
	if (check_args(args_count, args) == STATUS_FAIL)
		return (STATUS_FAIL);
	return (STATUS_SUCCESS);
}
