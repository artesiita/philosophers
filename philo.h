#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <limits.h>

# define PHILO_MAX_COUNT 200

typedef pthread_t		t_id;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

typedef struct s_mutexes
{
	t_mutex	*left_fork;
	t_mutex	*right_fork;
	t_mutex	*write_lock;
	t_mutex	*meal_lock;
}	t_mutexes;

typedef struct s_times
{
	size_t	die;
	size_t	eat;
	size_t	sleep;
	size_t	last_meal;
	size_t	born_time;
}	t_times;

typedef struct s_philo
{
	int			id;
	t_times		times;
	t_mutexes	mutexes;
	int			must_eat;
	t_id		thread_id;
	int			meals_eaten;
	int			philo_count;
}	t_philo;

typedef struct s_engine
{
	t_mutex	*forks;
	t_philo	*philos;
	t_mutex	meal_lock;
	t_mutex	write_lock;
}	t_engine;



/*
** ----- utils.c -------------------------------
*/
long    ft_atoi(char *str);
void	error_message(char *text, int signal);
int     ft_strlen(char *str);
/*
** ----- init.c --------------------------------
*/

/*
** -----  --------------------------------
*/


#endif