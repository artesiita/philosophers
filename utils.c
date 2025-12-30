/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lartes-s <lartes-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 12:58:58 by lartes-s          #+#    #+#             */
/*   Updated: 2025/12/30 13:06:46 by lartes-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_message(char *text)
{
	if (text)
		write(2, text, ft_strlen(text) + 1);
}

void	print_message(char *str, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(philo->mutexes.write_lock);
	time = get_time() - philo->times.born_time;
	printf("%zu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->mutexes.write_lock);
}

void	ft_usleep(size_t milliseconds)
{
	size_t start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
}

size_t	get_time(void)
{
	t_timeval time;

	if(gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}