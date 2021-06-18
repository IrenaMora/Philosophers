#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define ERROR_MALLOC "Error\nMemory did not allocated."
# define ERROR_WRONG_ARGS "Error\nWrong arguments."
# define ERROR_LARGE_ARGS "Error\nToo large values in arguments."
# define ERROR_SMALL_ARGS "Error\nToo small values in arguments."
# define ERROR_WRONG_ARGS_COUNT "Error\nWrong arguments count."

# define MILLISECONDS_IN_SECOND 1000
# define MICROSECONDS_IN_SECOND 1000000
# define MICROSECOND_IN_MILLISECOND 1000

# define FIRST_ARG 1
# define START_ARG_FOR_TIMES 2

# define MIN_ARGS_COUNT 5
# define MAX_ARGS_COUNT 6

# define MAX_TIME 100000
# define MIN_TIME 60
# define MAX_PHILOSOPHERS 200
# define MIN_PHILOSOPHERS 1
# define MAX_EATING_CHECK 100000

# define END_OF_FILE '\0'
# define BY_DEFAULT 0
# define NOT_CHECK -1

typedef enum e_status
{
	STATUS_FAIL = -1,
	STATUS_SUCCESS = 1
}				t_status;

typedef enum e_atoi
{
	ATOI_PHILOSOPHER = 1,
	ATOI_TIME = 2,
	ATOI_EATING_TIME = 3
}				t_atoi;

typedef struct s_philosophers
{
	int				is_exit;
	int				already;
	int				number;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	struct timeval	global_time;
	char			*eating_memory;
	int				eating_max;
	int				time_sleep;
	int				time_eat;
	int				time_dead;
	int				philosophies_count;
}				t_philosophers;

void		ft_usleep(int microsecond, t_philosophers *philosophers, \
int philosopher_number, struct timeval *time);
long long	get_time_different(struct timeval *last, int update_last_time);
long long	get_global_time(t_philosophers *philosophers);
void		check_for_death(t_philosophers *philosophers, int philosopher_number, \
struct timeval *time, int update_last_time);
void		put_forks(t_philosophers *philosophers, int philosopher_number);
void		take_forks(t_philosophers *philosophers, int philosopher_number, \
struct timeval *time);
void		*alive_philosophers(void *arg);

int			validate_args(int args_count, char **args);
void		*philosophers_malloc(t_philosophers **philosophers, \
char *philosophers_count);
void		philosophers_parse_args(int args_count, char **args, \
t_philosophers *philosophers);
void		philosophers_create_mutex(t_philosophers *philosophers);
void		philosophers_create_threads(t_philosophers *philosophers);
void		philosophers_dealloc(t_philosophers *philosophers);

void		define_error(char *str);
int			ft_atoi(char *str, int check);

#endif
