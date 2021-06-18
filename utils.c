#include "philosophers.h"

void	define_error(char *str)
{
	printf("%s\n", str);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_atoi_set_scopes(int check, int *max_value, int *min_value)
{
	if (check == ATOI_PHILOSOPHER)
	{
		*max_value = MAX_PHILOSOPHERS;
		*min_value = MIN_PHILOSOPHERS;
	}
	else if (check == ATOI_TIME)
	{
		*max_value = MAX_TIME;
		*min_value = MIN_TIME;
	}
	else
	{
		*min_value = 0;
		*max_value = MAX_EATING_CHECK;
	}
}

int 	ft_atoi_check_scopes(char *str, int position, int number, int min_value)
{
	if (str[position] != END_OF_FILE)
	{
		define_error(ERROR_WRONG_ARGS);
		return (STATUS_FAIL);
	}
	if (number < min_value)
	{
		define_error(ERROR_SMALL_ARGS);
		return (STATUS_FAIL);
	}
	return (STATUS_SUCCESS);
}

int	ft_atoi(char *str, int check)
{
	int	position;
	int	number;
	int	max_value;
	int	min_value;

	position = 0;
	number = 0;
	ft_atoi_set_scopes(check, &max_value, &min_value);
	if (!ft_isdigit(str[position]))
	{
		define_error(ERROR_WRONG_ARGS);
		return (STATUS_FAIL);
	}
	while (ft_isdigit(str[position]))
	{
		number = number * 10 + str[position++] - '0';
		if (number > max_value)
		{
			define_error(ERROR_LARGE_ARGS);
			return (STATUS_FAIL);
		}
	}
	if (ft_atoi_check_scopes(str, position, number, min_value) == STATUS_FAIL)
		return (STATUS_FAIL);
	return (number);
}
