/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:13:05 by lartes-s          #+#    #+#             */
/*   Updated: 2025/12/30 19:48:57 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->mutexes.meal_lock);
	if (get_time() - philo->times.last_meal >= time_to_die)
	{
		pthread_mutex_unlock(philo->mutexes.meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->mutexes.meal_lock);
	return (0);
}

int	check_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philos[0].must_eat == -1)
		return (0);
	while (i < philos[0].philo_count)
	{
		pthread_mutex_lock(philos[i].mutexes.meal_lock);
		if (philos[i].meals_eaten >= philos[i].must_eat)
			finished_eating++;
		pthread_mutex_unlock(philos[i].mutexes.meal_lock);
		i++;
	}
	if (finished_eating == philos[0].philo_count)
	{
		pthread_mutex_lock(philos[0].mutexes.dead_lock);
		*philos[0].dead = 1;
		pthread_mutex_unlock(philos[0].mutexes.dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)pointer;
	while (1)
	{
		i = 0;
		while (i < philos[0].philo_count)
		{
			if (philo_dead(&philos[i], philos[i].times.die))
			{
				print_message("died", RED, &philos[i]);
				pthread_mutex_lock(philos[i].mutexes.dead_lock);
				*philos[i].dead = 1;
				pthread_mutex_unlock(philos[i].mutexes.dead_lock);
				return (NULL);
			}
			i++;
		}
		if (check_all_ate(philos))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->mutexes.left_fork);
	print_message("has taken a fork", YELLOW, philo);
	pthread_mutex_lock(philo->mutexes.right_fork);
	print_message("has taken a fork", YELLOW, philo);
	print_message("is eating", GREEN, philo);
	pthread_mutex_lock(philo->mutexes.meal_lock);
	philo->times.last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->mutexes.meal_lock);
	ft_usleep(philo->times.eat);
	pthread_mutex_unlock(philo->mutexes.right_fork);
	pthread_mutex_unlock(philo->mutexes.left_fork);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->must_eat == 0)
		return (NULL);
	if (philo->philo_count == 1)
	{
		pthread_mutex_lock(philo->mutexes.left_fork);
		print_message("has taken a fork", YELLOW, philo);
		ft_usleep(philo->times.die);
		pthread_mutex_unlock(philo->mutexes.left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(20);
	while (dead_loop(philo) == 0)
	{
		eat_routine(philo);
		print_message("is sleeping", BLUE, philo);
		ft_usleep(philo->times.sleep);
		print_message("is thinking", CYAN, philo);
	}
	return (NULL);
}

/*
time_to_die 
time_to_eat 
time_to_sleep 
[number_of_times_each_philosopher_must_eat]
*/