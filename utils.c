/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 12:58:58 by lartes-s          #+#    #+#             */
/*   Updated: 2025/12/30 19:30:57 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->mutexes.dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->mutexes.dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->mutexes.dead_lock);
	return (0);
}

void	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
}

size_t	get_time(void)
{
	t_timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	cleanup(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < engine->philo_count)
	{
		pthread_mutex_destroy(&engine->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&engine->dead_lock);
	pthread_mutex_destroy(&engine->write_lock);
	pthread_mutex_destroy(&engine->meal_lock);
	free(engine->philos);
	free(engine->forks);
}
