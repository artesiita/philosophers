/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 12:58:37 by lartes-s          #+#    #+#             */
/*   Updated: 2025/12/30 19:52:18 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define RESET   "\033[0m"
# define RED     "\033[0;31m"
# define GREEN   "\033[0;32m"
# define YELLOW  "\033[0;93m"
# define BLUE    "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN    "\033[0;36m"
# define WHITE   "\033[0;37m"

typedef pthread_t		t_id;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

typedef struct s_mutexes
{
	t_mutex	*left_fork;
	t_mutex	*right_fork;
	t_mutex	*write_lock;
	t_mutex	*meal_lock;
	t_mutex	*dead_lock;
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
	int			*dead;
}	t_philo;

typedef struct s_engine
{
	t_mutex	*forks;
	t_philo	*philos;
	t_mutex	meal_lock;
	t_mutex	write_lock;
	t_mutex	dead_lock;
	t_times	times;
	size_t	start_time;
	int		philo_count;
	int		dead_flag;
}	t_engine;

/*
** ----- utils ---------------------------------
*/
size_t	get_time(void);
void	ft_usleep(size_t milliseconds);
void	cleanup(t_engine *engine);
/*
** ----- string utils ----------------------------
*/
void	print_message(char *str, char *color, t_philo *philo);
long	ft_atoi(char *str);
void	error_message(char *text);
int		ft_strlen(char *str);

/*
** ----- init -----------------------------------
*/
int		init_engine(t_engine *engine, int ac, char **av);
int		init_threads(t_engine *engine);
/*
** ----- routine --------------------------------
*/
void	*philo_routine(void *pointer);
void	*monitor(void *pointer);
int		dead_loop(t_philo *philo);

#endif
