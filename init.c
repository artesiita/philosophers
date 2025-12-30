/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 12:58:15 by lartes-s          #+#    #+#             */
/*   Updated: 2025/12/30 19:25:50 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->philo_count)
	{
		pthread_mutex_init(&engine->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&engine->meal_lock, NULL);
	pthread_mutex_init(&engine->write_lock, NULL);
	pthread_mutex_init(&engine->dead_lock, NULL);
}

void	init_philos(t_engine *engine, int ac, char **av)
{
	int	i;
	int	must_eat;

	i = 0;
	must_eat = -1;
	if (ac == 6)
		must_eat = (int)ft_atoi(av[5]);
	while (i < engine->philo_count)
	{
		engine->philos[i].id = i + 1;
		engine->philos[i].times = engine->times;
		engine->philos[i].times.born_time = engine->start_time;
		engine->philos[i].times.last_meal = engine->start_time;
		engine->philos[i].meals_eaten = 0;
		engine->philos[i].must_eat = must_eat;
		engine->philos[i].philo_count = engine->philo_count;
		engine->philos[i].mutexes.write_lock = &engine->write_lock;
		engine->philos[i].mutexes.meal_lock = &engine->meal_lock;
		engine->philos[i].mutexes.dead_lock = &engine->dead_lock;
		engine->philos[i].dead = &engine->dead_flag;
		engine->philos[i].mutexes.left_fork = &engine->forks[i];
		engine->philos[i].mutexes.right_fork = \
				&engine->forks[(i + 1) % engine->philo_count];
		i++;
	}
}

int	init_threads(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->philo_count)
	{
		engine->philos[i].times.last_meal = engine->start_time;
		if (pthread_create(&engine->philos[i].thread_id, NULL, &philo_routine,
				&engine->philos[i]) != 0)
			return ((error_message("Error creating thread\n")), 0);
		i++;
	}
	return (1);
}

int	init_engine(t_engine *engine, int ac, char **av)
{
	engine->philo_count = (int)ft_atoi(av[1]);
	engine->times.die = ft_atoi(av[2]);
	engine->times.eat = ft_atoi(av[3]);
	engine->times.sleep = ft_atoi(av[4]);
	engine->start_time = get_time();
	engine->philos = malloc(sizeof(t_philo) * engine->philo_count);
	if (!engine->philos)
		return (0);
	engine->forks = malloc(sizeof(t_mutex) * engine->philo_count);
	if (!engine->forks)
	{
		free(engine->philos);
		return (0);
	}
	init_mutexes(engine);
	init_philos(engine, ac, av);
	return (1);
}

/*number_of_philosophers 
time_to_die 
time_to_eat 
time_to_sleep 
[number_of_times_each_philosopher_must_eat]*/
